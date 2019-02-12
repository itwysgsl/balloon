#include "balloon.h"

#include <iostream>
#include <sstream>

void bytes_convert(std::string hex, unsigned char* output) {
    int hex_length = hex.length();

    unsigned char bytes[hex_length / 2];
    std::stringstream converter;
    for (int i = 0; i < hex_length; i += 2) {
        converter << std::hex << hex.substr(i, 2);
        int byte;
        converter >> byte;
        bytes[i / 2] = byte & 0xFF;
        converter.str(std::string());
        converter.clear();
    }

    memcpy(output, bytes, hex_length / 2);
}

std::string string_reverse(std::string str, bool tmpr = false) {
    std::string tmp;
    std::string result;
    for (int i = 0; i < str.length(); i += 2) {
        tmp = str.substr(i, 2);
        if (tmpr) {
            tmp = std::string(tmp.rbegin(), tmp.rend());
        }
        result = tmp + result;
    }

    return result;
}

std::string hex_convert(const char *data, int len) {
    const char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    std::string s(len * 2, ' ');
    for (int i = 0; i < len; ++i) {
        s[2 * i]     = hexmap[(data[i] & 0xF0) >> 4];
        s[2 * i + 1] = hexmap[data[i] & 0x0F];
    }

    return s;
}

int main() {
	std::string header_hex = "00000020bb8bd52977024e03e7c9b422216e59edf6f2c586570160351d1d080314b80000b071b4f7795341de25ad84a5faf0abd8036eb55a67cd6189b778f81eb1f2609742dd2e5cffff001f00000000";
	std::string salt_hex = "736f6d655f72616e646f6d5f737472696e67";

    char output[32];
	unsigned char bytes[80];
	unsigned char salt[80];
	bytes_convert(header_hex, bytes);
	bytes_convert(salt_hex, salt);

	const unsigned char *input = bytes;
	balloon(input, output, 80, salt, 18);

    std::string result_hash = string_reverse(hex_convert(output, 32));
    std::string test_hash = "5b1bdae35aed02cbfa91f2856f6bcc8fc7e4d812eb3a667e47fc300313bcc6d7";

	std::cout << "Hash: " << result_hash << std::endl;

    assert(result_hash == test_hash);
	return 0;
}
