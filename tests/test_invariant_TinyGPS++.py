import pytest
import ctypes
import struct


# Simulate the buffer handling behavior that TinyGPS++ would perform
# We model the unsafe strcpy/strcat behavior and test that safe alternatives
# would truncate or reject oversized inputs

MAX_FIELD_LENGTH = 15  # Typical TinyGPS++ internal buffer size for NMEA fields
MAX_SENTENCE_LENGTH = 120  # Typical NMEA sentence max length


def safe_copy_to_buffer(source: str, max_size: int) -> str:
    """Simulates safe, size-bounded buffer copy (strncpy equivalent)"""
    if source is None:
        return ""
    # Truncate to max_size - 1 to leave room for null terminator
    return source[:max_size - 1]


def safe_parse_nmea_field(field: str, max_field_size: int = MAX_FIELD_LENGTH) -> str:
    """Simulates safe NMEA field parsing with bounds checking"""
    if field is None:
        return ""
    if len(field) >= max_field_size:
        # Reject or truncate oversized field
        return field[:max_field_size - 1]
    return field


def simulate_buffer_write(data: str, buffer_size: int) -> tuple:
    """
    Simulates writing to a fixed-size buffer.
    Returns (written_data, overflow_detected)
    """
    if len(data) >= buffer_size:
        # Overflow would occur with unsafe functions
        overflow_detected = True
        # Safe version truncates
        written = data[:buffer_size - 1]
    else:
        overflow_detected = False
        written = data
    return written, overflow_detected


def validate_nmea_sentence(sentence: str, max_length: int = MAX_SENTENCE_LENGTH) -> bool:
    """Validates that an NMEA sentence doesn't exceed maximum length"""
    return len(sentence) <= max_length


@pytest.mark.parametrize("payload", [
    # 2x oversized payloads
    "A" * (MAX_FIELD_LENGTH * 2),
    "B" * (MAX_FIELD_LENGTH * 2),
    "$GPGGA," + "9" * (MAX_FIELD_LENGTH * 2),
    
    # 10x oversized payloads
    "C" * (MAX_FIELD_LENGTH * 10),
    "D" * (MAX_FIELD_LENGTH * 10),
    
    # Extremely large payloads
    "E" * 1024,
    "F" * 4096,
    "G" * 65536,
    
    # NMEA-like oversized sentences
    "$GPGGA," + ",".join(["9" * 20] * 15),
    "$GPRMC," + "A" * 500,
    "$GPGSV," + "B" * 1000,
    
    # Null bytes and special characters in oversized strings
    "X" * 100 + "\x00" + "Y" * 100,
    "\xff" * (MAX_FIELD_LENGTH * 5),
    "\x00" * (MAX_FIELD_LENGTH * 3),
    
    # Format string attack payloads (oversized)
    "%s" * 100,
    "%n" * 50,
    "%x" * 200,
    
    # Mixed content oversized
    "ABCDEF" * 50,
    "123456789" * 30,
    
    # Boundary conditions
    "A" * MAX_FIELD_LENGTH,           # Exactly at limit
    "A" * (MAX_FIELD_LENGTH + 1),     # One over limit
    "A" * (MAX_FIELD_LENGTH - 1),     # One under limit
    
    # NMEA sentence oversized fields
    "$GPGGA,123456.00," + "9" * 50 + ",N," + "9" * 50 + ",E,1,08,0.9,545.4,M,46.9,M,,*47",
    
    # Unicode/multibyte oversized
    "Ä" * (MAX_FIELD_LENGTH * 3),
    "中" * (MAX_FIELD_LENGTH * 2),
    
    # Whitespace padding attacks
    " " * (MAX_FIELD_LENGTH * 5),
    "\t" * (MAX_FIELD_LENGTH * 5),
    "\n" * (MAX_FIELD_LENGTH * 5),
    
    # Mixed attack payload
    "A" * 50 + "%s%n%x" + "B" * 50 + "\x00\xff" + "C" * 50,
])
def test_buffer_read_never_exceeds_declared_length(payload):
    """Invariant: Buffer reads must never exceed the declared buffer length.
    Any input exceeding the buffer size must be truncated or rejected,
    never causing out-of-bounds memory access."""
    
    buffer_size = MAX_FIELD_LENGTH
    
    # Test 1: Safe copy must never produce output exceeding buffer_size - 1
    result = safe_copy_to_buffer(payload, buffer_size)
    assert len(result) < buffer_size, (
        f"Buffer overflow: result length {len(result)} >= buffer size {buffer_size}. "
        f"Input length was {len(payload)}"
    )
    
    # Test 2: Safe field parsing must truncate oversized inputs
    parsed = safe_parse_nmea_field(payload, buffer_size)
    assert len(parsed) < buffer_size, (
        f"Field parser overflow: parsed length {len(parsed)} >= buffer size {buffer_size}. "
        f"Input length was {len(payload)}"
    )
    
    # Test 3: Buffer write simulation must detect overflow for oversized inputs
    written, overflow_detected = simulate_buffer_write(payload, buffer_size)
    assert len(written) < buffer_size, (
        f"Written data length {len(written)} >= buffer size {buffer_size}"
    )
    
    # Test 4: If input exceeds buffer, overflow must be detected
    if len(payload) >= buffer_size:
        assert overflow_detected, (
            f"Overflow not detected for input of length {len(payload)} "
            f"with buffer size {buffer_size}"
        )
    
    # Test 5: Written data must be a prefix of the original input (truncation, not corruption)
    if len(payload) > 0 and len(written) > 0:
        assert payload.startswith(written), (
            f"Written data is not a valid prefix of input. "
            f"Data corruption detected."
        )
    
    # Test 6: Result must not contain data beyond what was in the original input
    if len(result) > 0:
        assert result == payload[:len(result)], (
            f"Result contains unexpected data. Possible buffer read beyond input bounds."
        )


@pytest.mark.parametrize("sentence,expected_valid", [
    # Valid NMEA sentences (within bounds)
    ("$GPGGA,123456.00,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47", True),
    ("$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A", True),
    
    # Oversized sentences (should be rejected)
    ("$GPGGA," + "A" * 200, False),
    ("$GPRMC," + "B" * 500, False),
    ("$" + "X" * MAX_SENTENCE_LENGTH * 2, False),
    ("$GPGSV," + "9" * 1000, False),
])
def test_nmea_sentence_length_validation(sentence, expected_valid):
    """Invariant: NMEA sentences exceeding maximum length must be rejected."""
    is_valid = validate_nmea_sentence(sentence, MAX_SENTENCE_LENGTH)
    assert is_valid == expected_valid, (
        f"Sentence validation mismatch. "
        f"Sentence length: {len(sentence)}, "
        f"Max allowed: {MAX_SENTENCE_LENGTH}, "
        f"Expected valid: {expected_valid}, "
        f"Got valid: {is_valid}"
    )


@pytest.mark.parametrize("field_value,buffer_size", [
    ("A" * 100, 15),
    ("B" * 200, 15),
    ("C" * 1000, 15),
    ("\xff" * 50, 15),
    ("%s%n%x" * 20, 15),
    ("normal", 15),  # Should pass without truncation
    ("A" * 14, 15),  # Exactly fits
    ("A" * 15, 15),  # One too many - should truncate
])
def test_field_buffer_boundary_conditions(field_value, buffer_size):
    """Invariant: Field buffer writes must respect declared buffer boundaries."""
    result = safe_copy_to_buffer(field_value, buffer_size)
    
    # Critical invariant: result must always be strictly less than buffer_size
    # (accounting for null terminator)
    assert len(result) <= buffer_size - 1, (
        f"CRITICAL: Buffer boundary violated! "
        f"Result length {len(result)} exceeds max allowed {buffer_size - 1}. "
        f"This would cause buffer overflow in C code."
    )
    
    # Verify no data beyond input was read
    assert len(result) <= len(field_value), (
        f"Result is longer than input - impossible without buffer overread"
    )