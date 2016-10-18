/* Copyright (c) 2014-2015, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of Code Aurora Forum, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Alternatively, and instead of the terms immediately above, this
 * software may be relicensed by the recipient at their option under the
 * terms of the GNU General Public License version 2 ("GPL") and only
 * version 2.  If the recipient chooses to relicense the software under
 * the GPL, then the recipient shall replace all of the text immediately
 * above and including this paragraph with the text immediately below
 * and between the words START OF ALTERNATE GPL TERMS and END OF
 * ALTERNATE GPL TERMS and such notices and license terms shall apply
 * INSTEAD OF the notices and licensing terms given above.
 *
 * START OF ALTERNATE GPL TERMS
 *
 * Copyright (c) 2014-2015, The Linux Foundation. All rights reserved.
 *
 * This software was originally licensed under the Code Aurora Forum
 * Inc. Dual BSD/GPL License version 1.1 and relicensed as permitted
 * under the terms thereof by a recipient under the General Public
 * License Version 2.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * END OF ALTERNATE GPL TERMS
 *
 */
#ifndef __CRYPTO_MSM_QCE_H
#define __CRYPTO_MSM_QCE_H

#include <linux/types.h>
#include <linux/platform_device.h>
#include <linux/crypto.h>

#include <crypto/algapi.h>
#include <crypto/aes.h>
#include <crypto/des.h>
#include <crypto/sha.h>
#include <crypto/aead.h>
#include <crypto/authenc.h>
#include <crypto/scatterwalk.h>

/* SHA digest size  in bytes */
#define SHA256_DIGESTSIZE		32
#define SHA1_DIGESTSIZE			20

#define AES_CE_BLOCK_SIZE		16

/* key size in bytes */
#define HMAC_KEY_SIZE			(SHA1_DIGESTSIZE)    /* hmac-sha1 */
#define SHA_HMAC_KEY_SIZE		64
#define DES_KEY_SIZE			8
#define TRIPLE_DES_KEY_SIZE		24
#define AES128_KEY_SIZE			16
#define AES192_KEY_SIZE			24
#define AES256_KEY_SIZE			32
#define MAX_CIPHER_KEY_SIZE		AES256_KEY_SIZE

/* iv length in bytes */
#define AES_IV_LENGTH			16
#define DES_IV_LENGTH                   8
#define MAX_IV_LENGTH			AES_IV_LENGTH

/* Maximum number of bytes per transfer */
#define QCE_MAX_OPER_DATA		0xFF00

/* Maximum Nonce bytes  */
#define MAX_NONCE  16

typedef void (*qce_comp_func_ptr_t)(void *areq,
		unsigned char *icv, unsigned char *iv, int ret);

/* Cipher algorithms supported */
enum qce_cipher_alg_enum {
	CIPHER_ALG_DES = 0,
	CIPHER_ALG_3DES = 1,
	CIPHER_ALG_AES = 2,
	CIPHER_ALG_LAST
};

/* Hash and hmac algorithms supported */
enum qce_hash_alg_enum {
	QCE_HASH_SHA1   = 0,
	QCE_HASH_SHA256 = 1,
	QCE_HASH_SHA1_HMAC   = 2,
	QCE_HASH_SHA256_HMAC = 3,
	QCE_HASH_AES_CMAC = 4,
	QCE_HASH_LAST
};

/* Cipher encryption/decryption operations */
enum qce_cipher_dir_enum {
	QCE_ENCRYPT = 0,
	QCE_DECRYPT = 1,
	QCE_CIPHER_DIR_LAST
};

/* Cipher algorithms modes */
enum qce_cipher_mode_enum {
	QCE_MODE_CBC = 0,
	QCE_MODE_ECB = 1,
	QCE_MODE_CTR = 2,
	QCE_MODE_XTS = 3,
	QCE_MODE_CCM = 4,
	QCE_CIPHER_MODE_LAST
};

/* Cipher operation type */
enum qce_req_op_enum {
	QCE_REQ_ABLK_CIPHER = 0,
	QCE_REQ_ABLK_CIPHER_NO_KEY = 1,
	QCE_REQ_AEAD = 2,
	QCE_REQ_LAST
};

/* Algorithms/features supported in CE HW engine */
struct ce_hw_support {
	bool sha1_hmac_20; /* Supports 20 bytes of HMAC key*/
	bool sha1_hmac; /* supports max HMAC key of 64 bytes*/
	bool sha256_hmac; /* supports max HMAC key of 64 bytes*/
	bool sha_hmac; /* supports SHA1 and SHA256 MAX HMAC key of 64 bytes*/
	bool cmac;
	bool aes_key_192;
	bool aes_xts;
	bool aes_ccm;
	bool ota;
	bool aligned_only;
	bool bam;
	bool is_shared;
	bool hw_key;
	bool use_sw_aes_cbc_ecb_ctr_algo;
	bool use_sw_aead_algo;
	bool use_sw_aes_xts_algo;
	bool use_sw_ahash_algo;
	bool use_sw_hmac_algo;
	bool use_sw_aes_ccm_algo;
	bool clk_mgmt_sus_res;
	unsigned int ce_device;
	unsigned int ce_hw_instance;
};

/* Sha operation parameters */
struct qce_sha_req {
	qce_comp_func_ptr_t qce_cb;	/* call back */
	enum qce_hash_alg_enum alg;	/* sha algorithm */
	unsigned char *digest;		/* sha digest  */
	struct scatterlist *src;	/* pointer to scatter list entry */
	uint32_t  auth_data[4];		/* byte count */
	unsigned char *authkey;		/* auth key */
	unsigned int  authklen;		/* auth key length */
	bool first_blk;			/* first block indicator */
	bool last_blk;			/* last block indicator */
	unsigned int size;		/* data length in bytes */
	void *areq;
	unsigned int  flags;
};

struct qce_req {
	enum qce_req_op_enum op;	/* operation type */
	qce_comp_func_ptr_t qce_cb;	/* call back */
	void *areq;
	enum qce_cipher_alg_enum   alg;	/* cipher algorithms*/
	enum qce_cipher_dir_enum dir;	/* encryption? decryption? */
	enum qce_cipher_mode_enum mode;	/* algorithm mode  */
	enum qce_hash_alg_enum auth_alg;/* authentication algorithm for aead */
	unsigned char *authkey;		/* authentication key  */
	unsigned int authklen;		/* authentication key kength */
	unsigned int authsize;		/* authentication key kength */
	unsigned char  nonce[MAX_NONCE];/* nonce for ccm mode */
	unsigned char *assoc;		/* Ptr to formatted associated data */
	unsigned int assoclen;		/* Formatted associated data length  */
	struct scatterlist *asg;	/* Formatted associated data sg  */
	unsigned char *enckey;		/* cipher key  */
	unsigned int encklen;		/* cipher key length */
	unsigned char *iv;		/* initialization vector */
	unsigned int ivsize;		/* initialization vector size*/
	unsigned int cryptlen;		/* data length */
	unsigned int use_pmem;		/* is source of data PMEM allocated? */
	struct qcedev_pmem_info *pmem;	/* pointer to pmem_info structure*/
	unsigned int  flags;
};

struct qce_pm_table {
	int (*suspend)(void *handle);
	int (*resume)(void *handle);
};

extern struct qce_pm_table qce_pm_table;

void *qce_open(struct platform_device *pdev, int *rc);
int qce_close(void *handle);
int qce_aead_req(void *handle, struct qce_req *req);
int qce_ablk_cipher_req(void *handle, struct qce_req *req);
int qce_hw_support(void *handle, struct ce_hw_support *support);
int qce_process_sha_req(void *handle, struct qce_sha_req *s_req);
int qce_enable_clk(void *handle);
int qce_disable_clk(void *handle);

#endif /* __CRYPTO_MSM_QCE_H */
