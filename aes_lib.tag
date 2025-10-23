<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.14.0" doxygen_gitid="cbe58f6237b2238c9af7f51c6b7afb8bbf52c866">
  <compound kind="file">
    <name>aes_core.c</name>
    <path>Aes/aes/</path>
    <filename>aes__core_8c.html</filename>
    <includes id="crypto__common_8h" name="crypto_common.h" local="yes" import="no" module="no" objc="no">../include/crypto_common.h</includes>
    <includes id="aes__internal_8h" name="aes_internal.h" local="yes" import="no" module="no" objc="no">../include/aes_internal.h</includes>
    <includes id="aes_8h" name="aes.h" local="yes" import="no" module="no" objc="no">../include/aes.h</includes>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_decrypt_block</name>
      <anchorfile>aes__core_8c.html</anchorfile>
      <anchor>afe6a63a4b3f5064142440ca23b6a4952</anchor>
      <arglist>(const aes_key_t *dk, const uint8_t in[16u], uint8_t out[16u])</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_decrypt_round</name>
      <anchorfile>aes__core_8c.html</anchorfile>
      <anchor>a9bd3cf85f8e98b02ba8bc3c9e22fc0dc</anchor>
      <arglist>(aes_error_stack_t *error_stack, uint8_t state[16], const uint32_t *round_key)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_encrypt_block</name>
      <anchorfile>aes__core_8c.html</anchorfile>
      <anchor>aabb4e32418e37c7d6f89dbc105633188</anchor>
      <arglist>(const aes_key_t *ek, const uint8_t in[16u], uint8_t out[16u])</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_encrypt_round</name>
      <anchorfile>aes__core_8c.html</anchorfile>
      <anchor>ae11f9a625030669c3080a65fae2e2b4c</anchor>
      <arglist>(aes_error_stack_t *error_stack, uint8_t state[16], const uint32_t *round_key)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>copy_16_bytes</name>
      <anchorfile>aes__core_8c.html</anchorfile>
      <anchor>a37fd693441d4bfa533e46255ccd25b4c</anchor>
      <arglist>(const uint8_t src[16], uint8_t dst[16])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>aes_error.c</name>
    <path>Aes/aes/</path>
    <filename>aes__error_8c.html</filename>
    <includes id="crypto__common_8h" name="crypto_common.h" local="yes" import="no" module="no" objc="no">../include/crypto_common.h</includes>
    <member kind="function">
      <type>void</type>
      <name>aes_error_clear</name>
      <anchorfile>aes__error_8c.html</anchorfile>
      <anchor>abccf2cfd1fbf0c5bda4ed14e538de58e</anchor>
      <arglist>(aes_error_stack_t *stack)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_error_get_top</name>
      <anchorfile>aes__error_8c.html</anchorfile>
      <anchor>a1c9779f7f9811f96e882566c3d84d247</anchor>
      <arglist>(const aes_error_stack_t *stack)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_error_init</name>
      <anchorfile>aes__error_8c.html</anchorfile>
      <anchor>acfd34f28f784d3ec26e5a7c1ed7c70fd</anchor>
      <arglist>(aes_error_stack_t *stack, int max_depth)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>aes_error_pop</name>
      <anchorfile>aes__error_8c.html</anchorfile>
      <anchor>aa5f6d482daf72b8eb2070e541427d258</anchor>
      <arglist>(aes_error_stack_t *stack)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>aes_error_print_stack</name>
      <anchorfile>aes__error_8c.html</anchorfile>
      <anchor>a26e16f052f5994d46fe23d6f8de77b33</anchor>
      <arglist>(const aes_error_stack_t *stack)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_error_push</name>
      <anchorfile>aes__error_8c.html</anchorfile>
      <anchor>ae4e7a389931ab891c26e48406d354859</anchor>
      <arglist>(aes_error_stack_t *stack, int line, const char *file, const char *function, aes_err_t error_code, const char *message)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>aes_error_to_string</name>
      <anchorfile>aes__error_8c.html</anchorfile>
      <anchor>aa0057a01608071f2c0bca6e05792728a</anchor>
      <arglist>(aes_err_t error_code)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static aes_error_node_t *</type>
      <name>create_error_node</name>
      <anchorfile>aes__error_8c.html</anchorfile>
      <anchor>a8b0663fa18703d61049c872268ccdfa3</anchor>
      <arglist>(int line, const char *file, const char *function, aes_err_t error_code, const char *message)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>free_error_node</name>
      <anchorfile>aes__error_8c.html</anchorfile>
      <anchor>af9c31591ef6b8c2816fee7b888192a88</anchor>
      <arglist>(aes_error_node_t *node)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>aes_key.c</name>
    <path>Aes/aes/</path>
    <filename>aes__key_8c.html</filename>
    <includes id="aes_8h" name="aes.h" local="yes" import="no" module="no" objc="no">../include/aes.h</includes>
    <includes id="aes__internal_8h" name="aes_internal.h" local="yes" import="no" module="no" objc="no">../include/aes_internal.h</includes>
    <includes id="crypto__common_8h" name="crypto_common.h" local="yes" import="no" module="no" objc="no">../include/crypto_common.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MAX_ROUND_KEYS</name>
      <anchorfile>aes__key_8c.html</anchorfile>
      <anchor>a0ac19c0f0c3a57be6bce46f9431e36fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>aes_key_clear</name>
      <anchorfile>aes__key_8c.html</anchorfile>
      <anchor>a116a592bdaeb618423f3b9ed6e55de18</anchor>
      <arglist>(aes_key_t *k)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_set_decrypt_key</name>
      <anchorfile>aes__key_8c.html</anchorfile>
      <anchor>a62071da336b5ef76f4a986c57772ad51</anchor>
      <arglist>(aes_key_t *dk, const uint8_t *key, aes_keylen_t klen)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_set_encrypt_key</name>
      <anchorfile>aes__key_8c.html</anchorfile>
      <anchor>a3d945adb952dbd52d664512b57c1bef7</anchor>
      <arglist>(aes_key_t *ek, const uint8_t *key, aes_keylen_t klen)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static uint32_t</type>
      <name>bytes_to_word</name>
      <anchorfile>aes__key_8c.html</anchorfile>
      <anchor>a1170fba06800fe28546e0f3230b77b3f</anchor>
      <arglist>(const uint8_t *bytes, int index)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>copy_encrypt_to_decrypt_key</name>
      <anchorfile>aes__key_8c.html</anchorfile>
      <anchor>a45735928fb879e879cbba1871dc4e8e9</anchor>
      <arglist>(aes_key_t *dk, const aes_key_t *ek)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>generate_round_keys</name>
      <anchorfile>aes__key_8c.html</anchorfile>
      <anchor>aea0a70fdf33e4f1c6ee39dbcb054df3d</anchor>
      <arglist>(aes_key_t *ek, aes_keylen_t key_len, int rounds)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>get_rounds</name>
      <anchorfile>aes__key_8c.html</anchorfile>
      <anchor>ae21460dcf09e93fd850c1741f53aa6ad</anchor>
      <arglist>(aes_keylen_t key_len)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static uint32_t</type>
      <name>rot_word</name>
      <anchorfile>aes__key_8c.html</anchorfile>
      <anchor>a6532b120d3dd430a876edc2cba280203</anchor>
      <arglist>(uint32_t word)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>set_initial_round_keys</name>
      <anchorfile>aes__key_8c.html</anchorfile>
      <anchor>ac5e77982970505f64a0dca26fb5664b0</anchor>
      <arglist>(aes_key_t *ek, const uint8_t *key, aes_keylen_t key_len)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static uint32_t</type>
      <name>sub_word</name>
      <anchorfile>aes__key_8c.html</anchorfile>
      <anchor>afa4a5c146499358c4f1d07e863b107df</anchor>
      <arglist>(uint32_t word)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>aes_round.c</name>
    <path>Aes/aes/</path>
    <filename>aes__round_8c.html</filename>
    <includes id="crypto__common_8h" name="crypto_common.h" local="yes" import="no" module="no" objc="no">../include/crypto_common.h</includes>
    <includes id="aes__internal_8h" name="aes_internal.h" local="yes" import="no" module="no" objc="no">../include/aes_internal.h</includes>
    <includes id="gf256_8h" name="gf256.h" local="yes" import="no" module="no" objc="no">../include/gf256.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>COL_SIZE</name>
      <anchorfile>aes__round_8c.html</anchorfile>
      <anchor>a99468544016f0abb855e6415c629ec29</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ROW_SIZE</name>
      <anchorfile>aes__round_8c.html</anchorfile>
      <anchor>aa4d030604a90c8d019d90fc721900d63</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>STATE_SIZE</name>
      <anchorfile>aes__round_8c.html</anchorfile>
      <anchor>a7e3ce397037c8f4f14f7adc0b969b662</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>aes_add_round_key</name>
      <anchorfile>aes__round_8c.html</anchorfile>
      <anchor>a138b2103148f7baa9788d27d3d5e8bee</anchor>
      <arglist>(uint8_t state[16], const uint32_t *round_key)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_inv_mix_columns</name>
      <anchorfile>aes__round_8c.html</anchorfile>
      <anchor>a2aeccb744b89697a22756f31ecddb041</anchor>
      <arglist>(aes_error_stack_t *error_stack, uint8_t state[16])</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>aes_inv_shift_row</name>
      <anchorfile>aes__round_8c.html</anchorfile>
      <anchor>a2be32e7816ccd490f83154cf97ce7743</anchor>
      <arglist>(uint8_t state[16], int row, int shift_amount)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_inv_shift_rows</name>
      <anchorfile>aes__round_8c.html</anchorfile>
      <anchor>a96899db7863294eeee2edb242831e8a4</anchor>
      <arglist>(aes_error_stack_t *error_stack, uint8_t state[16])</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_inv_sub_bytes</name>
      <anchorfile>aes__round_8c.html</anchorfile>
      <anchor>a4b9796ce6d3462d75cfdd884b0a85d2d</anchor>
      <arglist>(aes_error_stack_t *error_stack, uint8_t state[16])</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_mix_columns</name>
      <anchorfile>aes__round_8c.html</anchorfile>
      <anchor>a1db7c809b6cac1522e6b60ba578b31b3</anchor>
      <arglist>(aes_error_stack_t *error_stack, uint8_t state[16])</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>aes_shift_row</name>
      <anchorfile>aes__round_8c.html</anchorfile>
      <anchor>a71ba82ba9f22a78134a7a235cdcd0c6f</anchor>
      <arglist>(uint8_t state[16], int row, int shift_amount)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_shift_rows</name>
      <anchorfile>aes__round_8c.html</anchorfile>
      <anchor>acc971d2cbb58112c6858fdb8ee7e5b96</anchor>
      <arglist>(aes_error_stack_t *error_stack, uint8_t state[16])</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_sub_bytes</name>
      <anchorfile>aes__round_8c.html</anchorfile>
      <anchor>a2c4054176b5df616605510f7be132870</anchor>
      <arglist>(aes_error_stack_t *error_stack, uint8_t state[16])</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static uint8_t</type>
      <name>get_state_byte</name>
      <anchorfile>aes__round_8c.html</anchorfile>
      <anchor>a524dd1cc9dfb77829501d6d55623f4f3</anchor>
      <arglist>(const uint8_t state[16], int row, int col)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>inv_mix_column</name>
      <anchorfile>aes__round_8c.html</anchorfile>
      <anchor>a63dd1e01dab34b9823ab763137fe429d</anchor>
      <arglist>(const uint8_t state[16], int col, uint8_t result[4])</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>mix_column</name>
      <anchorfile>aes__round_8c.html</anchorfile>
      <anchor>add9440e905931ad6f5596ebbc0e283c9</anchor>
      <arglist>(const uint8_t state[16], int col, uint8_t result[4])</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>set_state_byte</name>
      <anchorfile>aes__round_8c.html</anchorfile>
      <anchor>a3ea006746cfeb9876e608606752c8652</anchor>
      <arglist>(uint8_t state[16], int row, int col, uint8_t value)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>aes_sbox.c</name>
    <path>Aes/aes/</path>
    <filename>aes__sbox_8c.html</filename>
    <includes id="aes__internal_8h" name="aes_internal.h" local="yes" import="no" module="no" objc="no">../include/aes_internal.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>SBOX_SIZE</name>
      <anchorfile>aes__sbox_8c.html</anchorfile>
      <anchor>abd0be4107111d5f74e5515b2a3b3fa45</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>STATE_SIZE</name>
      <anchorfile>aes__sbox_8c.html</anchorfile>
      <anchor>a7e3ce397037c8f4f14f7adc0b969b662</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>aes_inv_sub_byte</name>
      <anchorfile>aes__sbox_8c.html</anchorfile>
      <anchor>a61cf170159427cac446d3acec363ee6c</anchor>
      <arglist>(uint8_t byte)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>aes_sub_byte</name>
      <anchorfile>aes__sbox_8c.html</anchorfile>
      <anchor>a2854734b55688549152a905a54647306</anchor>
      <arglist>(uint8_t byte)</arglist>
    </member>
    <member kind="variable">
      <type>const uint8_t</type>
      <name>aes_inv_sbox</name>
      <anchorfile>aes__sbox_8c.html</anchorfile>
      <anchor>a27e28e1d061e6739d0fad609ef934897</anchor>
      <arglist>[256]</arglist>
    </member>
    <member kind="variable">
      <type>const uint8_t</type>
      <name>aes_rcon</name>
      <anchorfile>aes__sbox_8c.html</anchorfile>
      <anchor>aeec9929b0ddc6a9d687bb081b08de351</anchor>
      <arglist>[11]</arglist>
    </member>
    <member kind="variable">
      <type>const uint8_t</type>
      <name>aes_sbox</name>
      <anchorfile>aes__sbox_8c.html</anchorfile>
      <anchor>ad7b64e105b79a0f410f46830cc6f8ce8</anchor>
      <arglist>[256]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>gf256.c</name>
    <path>Aes/aes/</path>
    <filename>gf256_8c.html</filename>
    <includes id="gf256_8h" name="gf256.h" local="yes" import="no" module="no" objc="no">../include/gf256.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>GF256_MSB</name>
      <anchorfile>gf256_8c.html</anchorfile>
      <anchor>a753ec5ba98e509d03ef02177c7008f31</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>GF256_POLY</name>
      <anchorfile>gf256_8c.html</anchorfile>
      <anchor>aa6dea0cab97bb7ff79e1fcb1eb53f2aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>GF256_SIZE</name>
      <anchorfile>gf256_8c.html</anchorfile>
      <anchor>a01cd56df8c168867921c6789a563d209</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_inv</name>
      <anchorfile>gf256_8c.html</anchorfile>
      <anchor>a43b3c7a9e2c10d25670fd961ae2916ca</anchor>
      <arglist>(uint8_t a)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_mul</name>
      <anchorfile>gf256_8c.html</anchorfile>
      <anchor>af1afff8141cfc915bb37fc01dab39995</anchor>
      <arglist>(uint8_t a, uint8_t b)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_mul2</name>
      <anchorfile>gf256_8c.html</anchorfile>
      <anchor>ab1a4c6e697471a80f248a5df6237283f</anchor>
      <arglist>(uint8_t a)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_mul3</name>
      <anchorfile>gf256_8c.html</anchorfile>
      <anchor>ae6a82b1e4b184ece8e847727af184569</anchor>
      <arglist>(uint8_t a)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_mul4</name>
      <anchorfile>gf256_8c.html</anchorfile>
      <anchor>ac267265694e3048a2d7e21db0fff887e</anchor>
      <arglist>(uint8_t a)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_mul8</name>
      <anchorfile>gf256_8c.html</anchorfile>
      <anchor>a9f0857dae2fc51046b94eef4c77ecf05</anchor>
      <arglist>(uint8_t a)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static uint8_t</type>
      <name>gf256_reduce</name>
      <anchorfile>gf256_8c.html</anchorfile>
      <anchor>a3fd35e82b574ff067e1edd0920426951</anchor>
      <arglist>(uint8_t value)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_sqrt</name>
      <anchorfile>gf256_8c.html</anchorfile>
      <anchor>aa1b0131553226bc010a968632bfd6a81</anchor>
      <arglist>(uint8_t a)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_square</name>
      <anchorfile>gf256_8c.html</anchorfile>
      <anchor>af2742711f8fb9972d6963500247c9ae7</anchor>
      <arglist>(uint8_t a)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const uint8_t</type>
      <name>gf256_inv_table</name>
      <anchorfile>gf256_8c.html</anchorfile>
      <anchor>a48805afcb13da28b7bdbea60d6fddec1</anchor>
      <arglist>[256]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>aes.h</name>
    <path>Aes/include/</path>
    <filename>aes_8h.html</filename>
    <includes id="crypto__common_8h" name="crypto_common.h" local="yes" import="no" module="no" objc="no">crypto_common.h</includes>
    <class kind="struct">aes_key_t</class>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_decrypt_block</name>
      <anchorfile>aes_8h.html</anchorfile>
      <anchor>afe6a63a4b3f5064142440ca23b6a4952</anchor>
      <arglist>(const aes_key_t *dk, const uint8_t in[16u], uint8_t out[16u])</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_encrypt_block</name>
      <anchorfile>aes_8h.html</anchorfile>
      <anchor>aabb4e32418e37c7d6f89dbc105633188</anchor>
      <arglist>(const aes_key_t *ek, const uint8_t in[16u], uint8_t out[16u])</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>aes_get_rounds</name>
      <anchorfile>aes_8h.html</anchorfile>
      <anchor>a81a470a964ab4f55d02fdcd373547390</anchor>
      <arglist>(aes_keylen_t klen)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>aes_get_version</name>
      <anchorfile>aes_8h.html</anchorfile>
      <anchor>a3f9692247f6c72de9af7faffa803be38</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>aes_is_valid_key_length</name>
      <anchorfile>aes_8h.html</anchorfile>
      <anchor>ac434d593ba8dfa95f9df3239aec09e56</anchor>
      <arglist>(aes_keylen_t klen)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>aes_key_clear</name>
      <anchorfile>aes_8h.html</anchorfile>
      <anchor>a116a592bdaeb618423f3b9ed6e55de18</anchor>
      <arglist>(aes_key_t *k)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_set_decrypt_key</name>
      <anchorfile>aes_8h.html</anchorfile>
      <anchor>a62071da336b5ef76f4a986c57772ad51</anchor>
      <arglist>(aes_key_t *dk, const uint8_t *key, aes_keylen_t klen)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_set_encrypt_key</name>
      <anchorfile>aes_8h.html</anchorfile>
      <anchor>a3d945adb952dbd52d664512b57c1bef7</anchor>
      <arglist>(aes_key_t *ek, const uint8_t *key, aes_keylen_t klen)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>aes_ctr.c</name>
    <path>Aes/include/</path>
    <filename>aes__ctr_8c.html</filename>
    <includes id="aes__ctr_8h" name="aes_ctr.h" local="yes" import="no" module="no" objc="no">aes_ctr.h</includes>
    <includes id="aes_8h" name="aes.h" local="yes" import="no" module="no" objc="no">aes.h</includes>
    <includes id="ctr__mode_8h" name="ctr_mode.h" local="yes" import="no" module="no" objc="no">ctr_mode.h</includes>
    <includes id="crypto__common_8h" name="crypto_common.h" local="yes" import="no" module="no" objc="no">crypto_common.h</includes>
    <member kind="function">
      <type>void</type>
      <name>aes_ctr_clear</name>
      <anchorfile>aes__ctr_8c.html</anchorfile>
      <anchor>a417c36f6e6803a52a972cef3bdc64e4b</anchor>
      <arglist>(aes_ctr_ctx_t *ctx)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_ctr_crypt</name>
      <anchorfile>aes__ctr_8c.html</anchorfile>
      <anchor>a3403d02e23057eeb02ac76a956799328</anchor>
      <arglist>(aes_ctr_ctx_t *ctx, const uint8_t *in, uint8_t *out, size_t len)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>aes_ctr_get_counter</name>
      <anchorfile>aes__ctr_8c.html</anchorfile>
      <anchor>ad6672313c2493af016e09d5cd9631601</anchor>
      <arglist>(const aes_ctr_ctx_t *ctx, uint8_t counter[16u])</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_ctr_init</name>
      <anchorfile>aes__ctr_8c.html</anchorfile>
      <anchor>ab3234a4a3b91a664ef4b46500b4637bb</anchor>
      <arglist>(aes_ctr_ctx_t *ctx, const uint8_t *key, aes_keylen_t klen, const uint8_t iv[16u])</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_ctr_set_counter</name>
      <anchorfile>aes__ctr_8c.html</anchorfile>
      <anchor>a9f379fc465a4700752169b33838cf66a</anchor>
      <arglist>(aes_ctr_ctx_t *ctx, const uint8_t counter[16u])</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>aes_encrypt_wrapper</name>
      <anchorfile>aes__ctr_8c.html</anchorfile>
      <anchor>ae1291aee1cb141f6cb09526feb71e711</anchor>
      <arglist>(const void *key, const uint8_t in[16], uint8_t out[16])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>aes_ctr.h</name>
    <path>Aes/include/</path>
    <filename>aes__ctr_8h.html</filename>
    <includes id="aes_8h" name="aes.h" local="yes" import="no" module="no" objc="no">aes.h</includes>
    <includes id="ctr__mode_8h" name="ctr_mode.h" local="yes" import="no" module="no" objc="no">ctr_mode.h</includes>
    <includes id="crypto__common_8h" name="crypto_common.h" local="yes" import="no" module="no" objc="no">crypto_common.h</includes>
    <class kind="struct">aes_ctr_ctx_t</class>
    <member kind="function">
      <type>void</type>
      <name>aes_ctr_clear</name>
      <anchorfile>aes__ctr_8h.html</anchorfile>
      <anchor>a417c36f6e6803a52a972cef3bdc64e4b</anchor>
      <arglist>(aes_ctr_ctx_t *ctx)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_ctr_crypt</name>
      <anchorfile>aes__ctr_8h.html</anchorfile>
      <anchor>a3403d02e23057eeb02ac76a956799328</anchor>
      <arglist>(aes_ctr_ctx_t *ctx, const uint8_t *in, uint8_t *out, size_t len)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>aes_ctr_get_counter</name>
      <anchorfile>aes__ctr_8h.html</anchorfile>
      <anchor>ad6672313c2493af016e09d5cd9631601</anchor>
      <arglist>(const aes_ctr_ctx_t *ctx, uint8_t counter[16u])</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_ctr_init</name>
      <anchorfile>aes__ctr_8h.html</anchorfile>
      <anchor>ab3234a4a3b91a664ef4b46500b4637bb</anchor>
      <arglist>(aes_ctr_ctx_t *ctx, const uint8_t *key, aes_keylen_t klen, const uint8_t iv[16u])</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_ctr_set_counter</name>
      <anchorfile>aes__ctr_8h.html</anchorfile>
      <anchor>a9f379fc465a4700752169b33838cf66a</anchor>
      <arglist>(aes_ctr_ctx_t *ctx, const uint8_t counter[16u])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>aes_internal.h</name>
    <path>Aes/include/</path>
    <filename>aes__internal_8h.html</filename>
    <includes id="crypto__common_8h" name="crypto_common.h" local="yes" import="no" module="no" objc="no">crypto_common.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>AES_RCON_SIZE</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>a6023b3c0a5c8ba45740a2fc164688f78</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AES_SBOX_SIZE</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>a52b903a32318ee03fd864231e021ab99</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AES_STATE_SIZE</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>ac13e93d70a634b204bc1f82f00e38803</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>aes_add_round_key</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>a138b2103148f7baa9788d27d3d5e8bee</anchor>
      <arglist>(uint8_t state[16], const uint32_t *round_key)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_decrypt_round</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>a9bd3cf85f8e98b02ba8bc3c9e22fc0dc</anchor>
      <arglist>(aes_error_stack_t *error_stack, uint8_t state[16], const uint32_t *round_key)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_encrypt_round</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>ae11f9a625030669c3080a65fae2e2b4c</anchor>
      <arglist>(aes_error_stack_t *error_stack, uint8_t state[16], const uint32_t *round_key)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_inv_mix_columns</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>a2aeccb744b89697a22756f31ecddb041</anchor>
      <arglist>(aes_error_stack_t *error_stack, uint8_t state[16])</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_inv_shift_rows</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>a96899db7863294eeee2edb242831e8a4</anchor>
      <arglist>(aes_error_stack_t *error_stack, uint8_t state[16])</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>aes_inv_sub_byte</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>a61cf170159427cac446d3acec363ee6c</anchor>
      <arglist>(uint8_t byte)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_inv_sub_bytes</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>a4b9796ce6d3462d75cfdd884b0a85d2d</anchor>
      <arglist>(aes_error_stack_t *error_stack, uint8_t state[16])</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_mix_columns</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>a1db7c809b6cac1522e6b60ba578b31b3</anchor>
      <arglist>(aes_error_stack_t *error_stack, uint8_t state[16])</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_shift_rows</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>acc971d2cbb58112c6858fdb8ee7e5b96</anchor>
      <arglist>(aes_error_stack_t *error_stack, uint8_t state[16])</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>aes_sub_byte</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>a2854734b55688549152a905a54647306</anchor>
      <arglist>(uint8_t byte)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_sub_bytes</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>a2c4054176b5df616605510f7be132870</anchor>
      <arglist>(aes_error_stack_t *error_stack, uint8_t state[16])</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_inv</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>a43b3c7a9e2c10d25670fd961ae2916ca</anchor>
      <arglist>(uint8_t a)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_mul</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>af1afff8141cfc915bb37fc01dab39995</anchor>
      <arglist>(uint8_t a, uint8_t b)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_mul2</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>ab1a4c6e697471a80f248a5df6237283f</anchor>
      <arglist>(uint8_t a)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_mul3</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>ae6a82b1e4b184ece8e847727af184569</anchor>
      <arglist>(uint8_t a)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_mul4</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>ac267265694e3048a2d7e21db0fff887e</anchor>
      <arglist>(uint8_t a)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_mul8</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>a9f0857dae2fc51046b94eef4c77ecf05</anchor>
      <arglist>(uint8_t a)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_sqrt</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>aa1b0131553226bc010a968632bfd6a81</anchor>
      <arglist>(uint8_t a)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_square</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>af2742711f8fb9972d6963500247c9ae7</anchor>
      <arglist>(uint8_t a)</arglist>
    </member>
    <member kind="variable">
      <type>const uint8_t</type>
      <name>aes_inv_sbox</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>a27e28e1d061e6739d0fad609ef934897</anchor>
      <arglist>[256]</arglist>
    </member>
    <member kind="variable">
      <type>const uint8_t</type>
      <name>aes_rcon</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>aeec9929b0ddc6a9d687bb081b08de351</anchor>
      <arglist>[11]</arglist>
    </member>
    <member kind="variable">
      <type>const uint8_t</type>
      <name>aes_sbox</name>
      <anchorfile>aes__internal_8h.html</anchorfile>
      <anchor>ad7b64e105b79a0f410f46830cc6f8ce8</anchor>
      <arglist>[256]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>crypto_common.h</name>
    <path>Aes/include/</path>
    <filename>crypto__common_8h.html</filename>
    <class kind="struct">aes_error_node</class>
    <class kind="struct">aes_error_stack_t</class>
    <member kind="define">
      <type>#define</type>
      <name>AES_BLOCK_SIZE</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>af19ab913a847ad1e91c5291215116de1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AES_ERROR_INIT</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a06b716a0aa2c016d717fbbb9efbbdcff</anchor>
      <arglist>(stack)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AES_ERROR_PUSH</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a2fc14190da9cb5c13ddb277f4892a0ad</anchor>
      <arglist>(stack, err, msg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AES_GCM_TAG_SIZE</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a0ce292759e77ea0a0a01e262a75a090a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AES_MAX_KEY_SIZE</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>ac3c936c490fa55c6836a5bcf0e5de40b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AES_MAX_ROUND_KEYS</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>ac81a0f7a6f6e3fe6bba1ec100035e67b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AES_MAX_ROUNDS</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a40b86a5961b2bf7ff53fc9b41abe1215</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct aes_error_node</type>
      <name>aes_error_node_t</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a28a3b7416f60fd7f5dc3c9ba958a581f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>aes_err_t</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a6f6a45ebc3cc7d6266454fb2ea284ec9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AES_OK</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a6f6a45ebc3cc7d6266454fb2ea284ec9aacf07636102724d2a7913911b0cf74b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AES_ERR_BAD_PARAM</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a6f6a45ebc3cc7d6266454fb2ea284ec9ac801e566a3ee28e29ae8ce218fb9ee2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AES_ERR_BAD_KEY_LEN</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a6f6a45ebc3cc7d6266454fb2ea284ec9ac87be250a93015fb0f06bbd47c4d5897</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AES_ERR_AUTH_FAIL</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a6f6a45ebc3cc7d6266454fb2ea284ec9a9a8c589c52910e7e94e146e6b1cbbae9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AES_ERR_MEMORY</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a6f6a45ebc3cc7d6266454fb2ea284ec9a63ebd33a98fdf81163048806038714ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AES_ERR_INVALID_STATE</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a6f6a45ebc3cc7d6266454fb2ea284ec9ab687791ff6b14350566ca97ec696f871</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AES_ERR_NOT_INIT</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a6f6a45ebc3cc7d6266454fb2ea284ec9a7b65138ce07e9fde4f9c9c7a8a3f7ab8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AES_ERR_OVERFLOW</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a6f6a45ebc3cc7d6266454fb2ea284ec9ab94c73dea76694caa7028f7900026409</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AES_ERR_UNDERFLOW</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a6f6a45ebc3cc7d6266454fb2ea284ec9ab47313a1978fa2680c6005f6138bc530</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AES_ERR_INTERNAL</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a6f6a45ebc3cc7d6266454fb2ea284ec9a53c5e303bb7e41f46039cb9de5a6490a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AES_ERR_SBOX_FAIL</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a6f6a45ebc3cc7d6266454fb2ea284ec9ae94911465e2d6d656f7f8a6879851f1a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AES_ERR_MIX_FAIL</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a6f6a45ebc3cc7d6266454fb2ea284ec9a17ce429cc5afb54ecc5985e562894869</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AES_ERR_SHIFT_FAIL</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a6f6a45ebc3cc7d6266454fb2ea284ec9a04caf2949582798ae5843bec7b36df2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AES_ERR_KEY_FAIL</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a6f6a45ebc3cc7d6266454fb2ea284ec9a4ae5e535a3df9b81d1fb552fd5d34dda</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AES_ERR_GF256_FAIL</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a6f6a45ebc3cc7d6266454fb2ea284ec9af46efb388a3f157b385fd0757637ddd1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>aes_keylen_t</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a1587dedca1dbc3203fe62fb73ed1bc83</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AES_128</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a1587dedca1dbc3203fe62fb73ed1bc83a62e1b5b14d75b29e9ddbd89723fd8835</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AES_192</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a1587dedca1dbc3203fe62fb73ed1bc83a552850501cf9e17912a9b1eec8d32a3c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>AES_256</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a1587dedca1dbc3203fe62fb73ed1bc83abbbaa60825067ef5ad16c6328483f8f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>aes_error_clear</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>abccf2cfd1fbf0c5bda4ed14e538de58e</anchor>
      <arglist>(aes_error_stack_t *stack)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_error_get_top</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a1c9779f7f9811f96e882566c3d84d247</anchor>
      <arglist>(const aes_error_stack_t *stack)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_error_init</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>acfd34f28f784d3ec26e5a7c1ed7c70fd</anchor>
      <arglist>(aes_error_stack_t *stack, int max_depth)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>aes_error_pop</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>aa5f6d482daf72b8eb2070e541427d258</anchor>
      <arglist>(aes_error_stack_t *stack)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>aes_error_print_stack</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>a26e16f052f5994d46fe23d6f8de77b33</anchor>
      <arglist>(const aes_error_stack_t *stack)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>aes_error_push</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>ae4e7a389931ab891c26e48406d354859</anchor>
      <arglist>(aes_error_stack_t *stack, int line, const char *file, const char *function, aes_err_t error_code, const char *message)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>aes_error_to_string</name>
      <anchorfile>crypto__common_8h.html</anchorfile>
      <anchor>aa0057a01608071f2c0bca6e05792728a</anchor>
      <arglist>(aes_err_t error_code)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ctr_mode.c</name>
    <path>Aes/include/</path>
    <filename>ctr__mode_8c.html</filename>
    <includes id="ctr__mode_8h" name="ctr_mode.h" local="yes" import="no" module="no" objc="no">ctr_mode.h</includes>
    <includes id="crypto__common_8h" name="crypto_common.h" local="yes" import="no" module="no" objc="no">crypto_common.h</includes>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>apply_padding</name>
      <anchorfile>ctr__mode_8c.html</anchorfile>
      <anchor>a299c54d577d5b669e75af7915625b591</anchor>
      <arglist>(const uint8_t *in, size_t len, uint8_t out[16])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ctr_clear</name>
      <anchorfile>ctr__mode_8c.html</anchorfile>
      <anchor>adb2f503614d93e3f42c03e970b39c616</anchor>
      <arglist>(ctr_ctx_t *ctx)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>ctr_crypt</name>
      <anchorfile>ctr__mode_8c.html</anchorfile>
      <anchor>a57819a9ba17923ee873ad6ec5722c445</anchor>
      <arglist>(ctr_ctx_t *ctx, const uint8_t *in, uint8_t *out, size_t len)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ctr_get_counter</name>
      <anchorfile>ctr__mode_8c.html</anchorfile>
      <anchor>ac3d8708954940e7a72d78ff585753d9c</anchor>
      <arglist>(const ctr_ctx_t *ctx, uint8_t counter[16])</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>ctr_init</name>
      <anchorfile>ctr__mode_8c.html</anchorfile>
      <anchor>ab375dad94607756aac0ea976a869b448</anchor>
      <arglist>(ctr_ctx_t *ctx, void *key, block_cipher_encrypt_t encrypt_fn, const uint8_t iv[16])</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>ctr_set_counter</name>
      <anchorfile>ctr__mode_8c.html</anchorfile>
      <anchor>a2d8c4d1cac28f3d87ffc55ecf7c35612</anchor>
      <arglist>(ctr_ctx_t *ctx, const uint8_t counter[16])</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>increment_counter</name>
      <anchorfile>ctr__mode_8c.html</anchorfile>
      <anchor>a92c1c231b5fe55edaf28294dcc5062f1</anchor>
      <arglist>(uint8_t counter[16])</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static size_t</type>
      <name>remove_padding</name>
      <anchorfile>ctr__mode_8c.html</anchorfile>
      <anchor>aac678ff5749217d4fa03c3dd8c478625</anchor>
      <arglist>(const uint8_t in[16])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ctr_mode.h</name>
    <path>Aes/include/</path>
    <filename>ctr__mode_8h.html</filename>
    <includes id="crypto__common_8h" name="crypto_common.h" local="yes" import="no" module="no" objc="no">crypto_common.h</includes>
    <class kind="struct">ctr_ctx_t</class>
    <member kind="typedef">
      <type>void(*</type>
      <name>block_cipher_encrypt_t</name>
      <anchorfile>ctr__mode_8h.html</anchorfile>
      <anchor>a6c5fe3d79d0134aab6538210d2670491</anchor>
      <arglist>)(const void *key, const uint8_t in[16], uint8_t out[16])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ctr_clear</name>
      <anchorfile>ctr__mode_8h.html</anchorfile>
      <anchor>adb2f503614d93e3f42c03e970b39c616</anchor>
      <arglist>(ctr_ctx_t *ctx)</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>ctr_crypt</name>
      <anchorfile>ctr__mode_8h.html</anchorfile>
      <anchor>a57819a9ba17923ee873ad6ec5722c445</anchor>
      <arglist>(ctr_ctx_t *ctx, const uint8_t *in, uint8_t *out, size_t len)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ctr_get_counter</name>
      <anchorfile>ctr__mode_8h.html</anchorfile>
      <anchor>ac3d8708954940e7a72d78ff585753d9c</anchor>
      <arglist>(const ctr_ctx_t *ctx, uint8_t counter[16])</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>ctr_init</name>
      <anchorfile>ctr__mode_8h.html</anchorfile>
      <anchor>ab375dad94607756aac0ea976a869b448</anchor>
      <arglist>(ctr_ctx_t *ctx, void *key, block_cipher_encrypt_t encrypt_fn, const uint8_t iv[16])</arglist>
    </member>
    <member kind="function">
      <type>aes_err_t</type>
      <name>ctr_set_counter</name>
      <anchorfile>ctr__mode_8h.html</anchorfile>
      <anchor>a2d8c4d1cac28f3d87ffc55ecf7c35612</anchor>
      <arglist>(ctr_ctx_t *ctx, const uint8_t counter[16])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>gf256.h</name>
    <path>Aes/include/</path>
    <filename>gf256_8h.html</filename>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_inv</name>
      <anchorfile>gf256_8h.html</anchorfile>
      <anchor>a43b3c7a9e2c10d25670fd961ae2916ca</anchor>
      <arglist>(uint8_t a)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_mul</name>
      <anchorfile>gf256_8h.html</anchorfile>
      <anchor>af1afff8141cfc915bb37fc01dab39995</anchor>
      <arglist>(uint8_t a, uint8_t b)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_mul2</name>
      <anchorfile>gf256_8h.html</anchorfile>
      <anchor>ab1a4c6e697471a80f248a5df6237283f</anchor>
      <arglist>(uint8_t a)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_mul3</name>
      <anchorfile>gf256_8h.html</anchorfile>
      <anchor>ae6a82b1e4b184ece8e847727af184569</anchor>
      <arglist>(uint8_t a)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_mul4</name>
      <anchorfile>gf256_8h.html</anchorfile>
      <anchor>ac267265694e3048a2d7e21db0fff887e</anchor>
      <arglist>(uint8_t a)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_mul8</name>
      <anchorfile>gf256_8h.html</anchorfile>
      <anchor>a9f0857dae2fc51046b94eef4c77ecf05</anchor>
      <arglist>(uint8_t a)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_sqrt</name>
      <anchorfile>gf256_8h.html</anchorfile>
      <anchor>aa1b0131553226bc010a968632bfd6a81</anchor>
      <arglist>(uint8_t a)</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>gf256_square</name>
      <anchorfile>gf256_8h.html</anchorfile>
      <anchor>af2742711f8fb9972d6963500247c9ae7</anchor>
      <arglist>(uint8_t a)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>test_aes.c</name>
    <path>Aes/</path>
    <filename>test__aes_8c.html</filename>
    <includes id="aes_8h" name="aes.h" local="yes" import="no" module="no" objc="no">include/aes.h</includes>
    <includes id="aes__ctr_8h" name="aes_ctr.h" local="yes" import="no" module="no" objc="no">include/aes_ctr.h</includes>
    <includes id="crypto__common_8h" name="crypto_common.h" local="yes" import="no" module="no" objc="no">include/crypto_common.h</includes>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchorfile>test__aes_8c.html</anchorfile>
      <anchor>ae66f6b31b5ad750f1fe042a706a4e3d4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_hex</name>
      <anchorfile>test__aes_8c.html</anchorfile>
      <anchor>af2b06c0675671c7d946efdc4daf30946</anchor>
      <arglist>(const char *label, const uint8_t *data, size_t len)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_string</name>
      <anchorfile>test__aes_8c.html</anchorfile>
      <anchor>aeac05c1380dbf4c4bd1ff5126ab3f8e1</anchor>
      <arglist>(const char *label, const uint8_t *data, size_t len)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>test_aes_ctr_counter_operations</name>
      <anchorfile>test__aes_8c.html</anchorfile>
      <anchor>ab23ccd1ecad72c89489819a3421e495f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>test_aes_ctr_different_keys</name>
      <anchorfile>test__aes_8c.html</anchorfile>
      <anchor>a616b25eee0df7b84fe27ac63a2fb8f9d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>test_aes_ctr_error_handling</name>
      <anchorfile>test__aes_8c.html</anchorfile>
      <anchor>a3498c5706b5f7d150a392f9ef5462ad2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>test_aes_ctr_padding</name>
      <anchorfile>test__aes_8c.html</anchorfile>
      <anchor>aa5e00509925efba0c0f66943ba1bb90a</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>aes_ctr_ctx_t</name>
    <filename>structaes__ctr__ctx__t.html</filename>
    <member kind="variable">
      <type>ctr_ctx_t</type>
      <name>ctr</name>
      <anchorfile>structaes__ctr__ctx__t.html</anchorfile>
      <anchor>acc147f72beefe2e6a5111797c5bac790</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>aes_key_t</type>
      <name>ek</name>
      <anchorfile>structaes__ctr__ctx__t.html</anchorfile>
      <anchor>ad08d72e6809105ceec7fd08565370587</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>aes_error_node</name>
    <filename>structaes__error__node.html</filename>
    <member kind="variable">
      <type>aes_err_t</type>
      <name>error_code</name>
      <anchorfile>structaes__error__node.html</anchorfile>
      <anchor>a6f40c9e559c6961b1baad7de52adc537</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>file</name>
      <anchorfile>structaes__error__node.html</anchorfile>
      <anchor>aa188097f809551f749b00e8eebe432a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>function</name>
      <anchorfile>structaes__error__node.html</anchorfile>
      <anchor>ac85cb263a8051eb61127b56290fe2861</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>line</name>
      <anchorfile>structaes__error__node.html</anchorfile>
      <anchor>aa32736d122a62b58908e3b4bd07a9c3b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>message</name>
      <anchorfile>structaes__error__node.html</anchorfile>
      <anchor>a79ed72dda117d49654ae86d03f341a95</anchor>
      <arglist>[256]</arglist>
    </member>
    <member kind="variable">
      <type>struct aes_error_node *</type>
      <name>next</name>
      <anchorfile>structaes__error__node.html</anchorfile>
      <anchor>ade5f03f4bf7a3d4911e88a080a517fcc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>aes_error_stack_t</name>
    <filename>structaes__error__stack__t.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>count</name>
      <anchorfile>structaes__error__stack__t.html</anchorfile>
      <anchor>aa318b6ddfa2e9ed8919bc4ce887a52d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>aes_error_node_t *</type>
      <name>head</name>
      <anchorfile>structaes__error__stack__t.html</anchorfile>
      <anchor>a31c7d4ce07eea520669d65d263f43cb4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>max_depth</name>
      <anchorfile>structaes__error__stack__t.html</anchorfile>
      <anchor>aec0e19e5fe066a32804f7606fa719ecd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>aes_key_t</name>
    <filename>structaes__key__t.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>nr</name>
      <anchorfile>structaes__key__t.html</anchorfile>
      <anchor>a7fba7f88334c26fd7de190011e062dfd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>rk</name>
      <anchorfile>structaes__key__t.html</anchorfile>
      <anchor>a37999aeb173d48c365afff16c93eedc1</anchor>
      <arglist>[60u]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ctr_ctx_t</name>
    <filename>structctr__ctx__t.html</filename>
    <member kind="variable">
      <type>uint8_t</type>
      <name>counter</name>
      <anchorfile>structctr__ctx__t.html</anchorfile>
      <anchor>a283485d302473a061dab12f4192c67fa</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable">
      <type>block_cipher_encrypt_t</type>
      <name>encrypt_fn</name>
      <anchorfile>structctr__ctx__t.html</anchorfile>
      <anchor>a321fca44dc8074411a02ab86fd8f86cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void *</type>
      <name>key</name>
      <anchorfile>structctr__ctx__t.html</anchorfile>
      <anchor>a2355d6664e3d32e8dcf4f189915df6ef</anchor>
      <arglist></arglist>
    </member>
  </compound>
</tagfile>
