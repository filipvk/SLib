/*
 *   Copyright (c) 2008-2018 SLIBIO <https://github.com/SLIBIO>
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *   THE SOFTWARE.
 */

#ifndef CHECKHEADER_SLIB_CRYPTO_RSA
#define CHECKHEADER_SLIB_CRYPTO_RSA

#include "definition.h"

#include "hash.h"

#include "../math/bigint.h"

namespace slib
{
	
	class SLIB_EXPORT RSAPublicKey
	{
	public:
		BigInt N; // modulus
		BigInt E; // public exponent
	
	public:
		RSAPublicKey();

		~RSAPublicKey();

	public:
		sl_uint32 getLength() const;

	};
	
	class SLIB_EXPORT RSAPrivateKey
	{
	public:
		BigInt N; // modulus
		BigInt E; // public exponent
		BigInt D; // private exponent
		BigInt P; // prime 1
		BigInt Q; // prime 2
		BigInt DP; // exponent1, D mod (P-1)
		BigInt DQ; // exponent2, D mod (Q-1)
		BigInt IQ; // Q^-1 mod P

		// Use N and D only for decryption
		sl_bool flagUseOnlyD = sl_false;
	
	public:
		RSAPrivateKey();

		~RSAPrivateKey();

	public:
		sl_uint32 getLength() const;

	};
	
	class SLIB_EXPORT RSA
	{
	public:
		static sl_bool executePublic(const RSAPublicKey& key, const void* src, void* dst);

		static sl_bool executePrivate(const RSAPrivateKey& key, const void* src, void* dst);
	
		/*
			PKCS#1 v1.5 Random Padding
		*/
		static sl_bool encryptPublic_pkcs1_v15(const RSAPublicKey& key, const void* input, sl_uint32 sizeInput, void* output);

		static sl_bool encryptPrivate_pkcs1_v15(const RSAPrivateKey& key, const void* input, sl_uint32 sizeInput, void* output);

		static sl_uint32 decryptPublic_pkcs1_v15(const RSAPublicKey& key, const void* input, void* output, sl_uint32 sizeOutputBuffer, sl_bool* pFlagSign = sl_null);

		static sl_uint32 decryptPrivate_pkcs1_v15(const RSAPrivateKey& key, const void* input, void* output, sl_uint32 sizeOutputBuffer, sl_bool* pFlagSign = sl_null);
	
		/*
			PKCS#1 v2.1 OAEP - Optimal Asymmetric Encryption Padding
		*/
		static sl_bool encryptPublic_oaep_v21(const RSAPublicKey& key, const Ref<CryptoHash>& hash, const void* input, sl_uint32 sizeInput, void* output, const void* label = 0, sl_uint32 sizeLabel = 0);

		static sl_bool encryptPrivate_oaep_v21(const RSAPrivateKey& key, const Ref<CryptoHash>& hash, const void* input, sl_uint32 sizeInput, void* output, const void* label = 0, sl_uint32 sizeLabel = 0);

		static sl_uint32 decryptPublic_oaep_v21(const RSAPublicKey& key, const Ref<CryptoHash>& hash, const void* input, void* output, sl_uint32 sizeOutputBuffer, const void* label = 0, sl_uint32 sizeLabel = 0);

		static sl_uint32 decryptPrivate_oaep_v21(const RSAPrivateKey& key, const Ref<CryptoHash>& hash, const void* input, void* output, sl_uint32 sizeOutputBuffer, const void* label = 0, sl_uint32 sizeLabel = 0);
	
	};

}

#endif

