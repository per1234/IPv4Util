/*
 * IPv4Util
 *
 * Copyright (C) 2013, Arno Moonen <info@arnom.nl>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
 * permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 * 
 * - The above copyright notice and this permission notice shall be included in all
 *   copies or substantial portions of the Software.
 *
 * - THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 *   INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 *   PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *   HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *   OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 *   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdint.h>

namespace IPv4Util
{
	bool onSameNetwork(uint8_t subnet[4], uint8_t ip_a[4], uint8_t ip_b[4]) {
		for(uint8_t i = 3; i >= 0; i--) {
			if( (ip_a[i] & subnet[i]) != (ip_b[i] & subnet[i]) ) {
				return false;
			}
		}
		return true;
	}
	
	bool isZeroNetworkBroadcast(uint8_t ip[4]) {
		for(uint8_t i = 3; i >= 0; i--) {
			if(ip[i] != 255) {
				return false;
			}
		}
		return true;
	}

	char getClassOfNetwork(uint8_t ip[4]) {
		if(ip[0] >= 240) {
			return 'E';
		}
		if(ip[0] >= 224) {
			return 'D'; // multicast
		}
		if(ip[0] >= 192) {
			return 'C';
		}
		if(ip[0] >= 128) {
			return 'B';
		}
		return 'A';
	}

	void getNetworkAddress(uint8_t subnet[4], uint8_t ip[4], uint8_t (&result)[4]) {
		for(uint8_t i = 0; i < 4; i++) {
			result[i] = (ip[i] & subnet[i]);
		}
	}

	void getBroadcastAddress(uint8_t subnet[4], uint8_t ip[4], uint8_t (&result)[4]) {
		for(uint8_t i = 0; i < 4; i++) {
			result[i] = (ip[i] & subnet[i]) | ~subnet[i];
		}
	}
}