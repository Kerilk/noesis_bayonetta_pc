typedef struct bayoMatType_s {
	bool known;
	char * shader_name;
	short size;
	short sampler_number;
	short color_1_sampler; //sampler2D
	short color_2_sampler; //sampler2D
	short color_3_sampler; //sampler2D
	short effectmap_sampler; //sampler2D
	short env_amb_sampler; //samplerCUBE
	short envmap_sampler; //samplerCUBE
	short lightmap_sampler; //sampler2D
	short refractmap_sampler; //sampler2D
	short reliefmap_sampler; //sampler2D
	short spec_mask_sampler; //sampler2D
	short spec_pow_sampler; //sampler2D
	short ambient; //float3
	short b_down; //float
	short bias; //float
	short blend; //float
	short blend_func; //float
	short color_1_offset; //float2
	short color_1_tile; //float2
	short color_2_offset; //float2
	short color_2_tile; //float2
	short color_3_offset; //float2
	short color_3_tile; //float2
	short depth; //float
	short diffuse; //float3
	short diffuse2; //float3
	short dist; //float
	short distortion; //float
	short dot_color; //float3
	short dot_max; //float
	short dot_min; //float
	short effect_offset; //float2
	short effectmap_tile; //float2
	short env_amb_param; //float
	short env_distortion; //float
	short env_factor; //float
	short esss_blend; //float
	short finalcolor_enhance; //float4
	short fog; //float3
	short fogfar; //float
	short fognear; //float
	short fresnel_max; //float
	short l_diffuse; //float3
	short light_col; //float3
	short light_col2; //float3
	short lightpos; //float4
	short lightpos2; //float4
	short prefogcolor_enhance; //float4
	short ref_blend; //float
	short refract_blend; //float
	short refract_distortion; //float
	short shadow_distortion; //float
	short shine; //float
	short spec_limit; //float
	short spec_type; //float
	short specular; //float3
	short spelightpos; //float4
	short sss_color; //float3
	short sss_flag; //float
	short sss_norm; //float2
	short sss_value; //float
	short test_color; //float3
	short test_func; //float
	short tex_blend; //float2
	short tile; //float2
} bayoMatType_t;
static void bayoUnsetMatType(bayoMatType_t &mat) {
	mat.known = false;
	mat.shader_name = NULL;
	mat.size = 0;
	mat.sampler_number = 0;
	mat.color_1_sampler = -1;
	mat.color_2_sampler = -1;
	mat.color_3_sampler = -1;
	mat.effectmap_sampler = -1;
	mat.env_amb_sampler = -1;
	mat.envmap_sampler = -1;
	mat.lightmap_sampler = -1;
	mat.refractmap_sampler = -1;
	mat.reliefmap_sampler = -1;
	mat.spec_mask_sampler = -1;
	mat.spec_pow_sampler = -1;
	mat.ambient = -1;
	mat.b_down = -1;
	mat.bias = -1;
	mat.blend = -1;
	mat.blend_func = -1;
	mat.color_1_offset = -1;
	mat.color_1_tile = -1;
	mat.color_2_offset = -1;
	mat.color_2_tile = -1;
	mat.color_3_offset = -1;
	mat.color_3_tile = -1;
	mat.depth = -1;
	mat.diffuse = -1;
	mat.diffuse2 = -1;
	mat.dist = -1;
	mat.distortion = -1;
	mat.dot_color = -1;
	mat.dot_max = -1;
	mat.dot_min = -1;
	mat.effect_offset = -1;
	mat.effectmap_tile = -1;
	mat.env_amb_param = -1;
	mat.env_distortion = -1;
	mat.env_factor = -1;
	mat.esss_blend = -1;
	mat.finalcolor_enhance = -1;
	mat.fog = -1;
	mat.fogfar = -1;
	mat.fognear = -1;
	mat.fresnel_max = -1;
	mat.l_diffuse = -1;
	mat.light_col = -1;
	mat.light_col2 = -1;
	mat.lightpos = -1;
	mat.lightpos2 = -1;
	mat.prefogcolor_enhance = -1;
	mat.ref_blend = -1;
	mat.refract_blend = -1;
	mat.refract_distortion = -1;
	mat.shadow_distortion = -1;
	mat.shine = -1;
	mat.spec_limit = -1;
	mat.spec_type = -1;
	mat.specular = -1;
	mat.spelightpos = -1;
	mat.sss_color = -1;
	mat.sss_flag = -1;
	mat.sss_norm = -1;
	mat.sss_value = -1;
	mat.test_color = -1;
	mat.test_func = -1;
	mat.tex_blend = -1;
	mat.tile = -1;
}
static void bayoSetMatType(bayoMatType_t &mat,
                           char * shader_name,
                           short size,
                           short sampler_number,
                           short color_1_sampler,
                           short color_2_sampler,
                           short color_3_sampler,
                           short effectmap_sampler,
                           short env_amb_sampler,
                           short envmap_sampler,
                           short lightmap_sampler,
                           short refractmap_sampler,
                           short reliefmap_sampler,
                           short spec_mask_sampler,
                           short spec_pow_sampler,
                           short ambient,
                           short b_down,
                           short bias,
                           short blend,
                           short blend_func,
                           short color_1_offset,
                           short color_1_tile,
                           short color_2_offset,
                           short color_2_tile,
                           short color_3_offset,
                           short color_3_tile,
                           short depth,
                           short diffuse,
                           short diffuse2,
                           short dist,
                           short distortion,
                           short dot_color,
                           short dot_max,
                           short dot_min,
                           short effect_offset,
                           short effectmap_tile,
                           short env_amb_param,
                           short env_distortion,
                           short env_factor,
                           short esss_blend,
                           short finalcolor_enhance,
                           short fog,
                           short fogfar,
                           short fognear,
                           short fresnel_max,
                           short l_diffuse,
                           short light_col,
                           short light_col2,
                           short lightpos,
                           short lightpos2,
                           short prefogcolor_enhance,
                           short ref_blend,
                           short refract_blend,
                           short refract_distortion,
                           short shadow_distortion,
                           short shine,
                           short spec_limit,
                           short spec_type,
                           short specular,
                           short spelightpos,
                           short sss_color,
                           short sss_flag,
                           short sss_norm,
                           short sss_value,
                           short test_color,
                           short test_func,
                           short tex_blend,
                           short tile) {
	mat.known = true;
	mat.shader_name = shader_name;
	mat.size = size;
	mat.sampler_number = sampler_number;
	mat.color_1_sampler = color_1_sampler;
	mat.color_2_sampler = color_2_sampler;
	mat.color_3_sampler = color_3_sampler;
	mat.effectmap_sampler = effectmap_sampler;
	mat.env_amb_sampler = env_amb_sampler;
	mat.envmap_sampler = envmap_sampler;
	mat.lightmap_sampler = lightmap_sampler;
	mat.refractmap_sampler = refractmap_sampler;
	mat.reliefmap_sampler = reliefmap_sampler;
	mat.spec_mask_sampler = spec_mask_sampler;
	mat.spec_pow_sampler = spec_pow_sampler;
	mat.ambient = ambient;
	mat.b_down = b_down;
	mat.bias = bias;
	mat.blend = blend;
	mat.blend_func = blend_func;
	mat.color_1_offset = color_1_offset;
	mat.color_1_tile = color_1_tile;
	mat.color_2_offset = color_2_offset;
	mat.color_2_tile = color_2_tile;
	mat.color_3_offset = color_3_offset;
	mat.color_3_tile = color_3_tile;
	mat.depth = depth;
	mat.diffuse = diffuse;
	mat.diffuse2 = diffuse2;
	mat.dist = dist;
	mat.distortion = distortion;
	mat.dot_color = dot_color;
	mat.dot_max = dot_max;
	mat.dot_min = dot_min;
	mat.effect_offset = effect_offset;
	mat.effectmap_tile = effectmap_tile;
	mat.env_amb_param = env_amb_param;
	mat.env_distortion = env_distortion;
	mat.env_factor = env_factor;
	mat.esss_blend = esss_blend;
	mat.finalcolor_enhance = finalcolor_enhance;
	mat.fog = fog;
	mat.fogfar = fogfar;
	mat.fognear = fognear;
	mat.fresnel_max = fresnel_max;
	mat.l_diffuse = l_diffuse;
	mat.light_col = light_col;
	mat.light_col2 = light_col2;
	mat.lightpos = lightpos;
	mat.lightpos2 = lightpos2;
	mat.prefogcolor_enhance = prefogcolor_enhance;
	mat.ref_blend = ref_blend;
	mat.refract_blend = refract_blend;
	mat.refract_distortion = refract_distortion;
	mat.shadow_distortion = shadow_distortion;
	mat.shine = shine;
	mat.spec_limit = spec_limit;
	mat.spec_type = spec_type;
	mat.specular = specular;
	mat.spelightpos = spelightpos;
	mat.sss_color = sss_color;
	mat.sss_flag = sss_flag;
	mat.sss_norm = sss_norm;
	mat.sss_value = sss_value;
	mat.test_color = test_color;
	mat.test_func = test_func;
	mat.tex_blend = tex_blend;
	mat.tile = tile;
}

bayoMatType_t bayoMatTypes[256];

static void bayoSetMatTypes(void) {
	for(int i=0; i<256; i++) {
		bayoUnsetMatType(bayoMatTypes[i]);
	}
	bayoSetMatType(bayoMatTypes[0x30], "modelshaderbgs00_xxxxx", 104, 1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 40, 72, 56, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x31], "modelshaderbgs01_xxxxx", 192, 3, 4, -1, -1, -1, -1, -1, 8, -1, 12, -1, -1, -1, -1, 32, -1, -1, -1, 16, -1, -1, -1, -1, 48, 80, 176, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 112, 144, 128, -1, -1, -1, -1, -1, 160, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 64);
	bayoSetMatType(bayoMatTypes[0x32], "modelshaderbgs02_xxxxx", 228, 4, 4, -1, -1, -1, -1, 16, 8, -1, 12, -1, -1, -1, -1, 36, 84, -1, -1, 20, -1, -1, -1, -1, 52, 116, 212, -1, -1, -1, -1, -1, -1, -1, 100, -1, -1, -1, -1, 148, 180, 164, -1, -1, -1, -1, -1, 196, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 68);
	bayoSetMatType(bayoMatTypes[0x33], "modelshaderbgs04_xxxxx", 212, 4, 4, 8, -1, -1, -1, -1, 12, -1, 16, -1, -1, -1, -1, 52, -1, -1, -1, 20, -1, 36, -1, -1, 68, 100, 196, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 132, 164, 148, -1, -1, -1, -1, -1, 180, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84);
	bayoSetMatType(bayoMatTypes[0x34], "modelshaderbgs05_xxxxx", 248, 5, 4, 8, -1, -1, -1, 20, 12, -1, 16, -1, -1, -1, -1, 56, 104, -1, -1, 24, -1, 40, -1, -1, 72, 136, 232, -1, -1, -1, -1, -1, -1, -1, 120, -1, -1, -1, -1, 168, 200, 184, -1, -1, -1, -1, -1, 216, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 88);
	bayoSetMatType(bayoMatTypes[0x35], "modelshaderbgs06_xxxxx", 232, 5, 4, 8, 12, -1, -1, -1, 16, -1, 20, -1, -1, -1, -1, 72, -1, -1, -1, 24, -1, 40, -1, 56, 88, 120, 216, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 152, 184, 168, -1, -1, -1, -1, -1, 200, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 104);
	bayoSetMatType(bayoMatTypes[0x36], "modelshaderbgs07_xxxxx", 356, 4, 4, -1, -1, 16, -1, 12, 8, -1, -1, -1, -1, -1, -1, 36, 84, 164, -1, 20, -1, -1, -1, -1, 52, 212, 340, 100, -1, -1, -1, -1, -1, -1, -1, 132, -1, -1, -1, 260, 292, 276, -1, -1, -1, -1, -1, 324, -1, -1, -1, 116, 148, -1, -1, -1, -1, -1, -1, -1, -1, -1, 196, 180, -1, 68);
	bayoSetMatType(bayoMatTypes[0x38], "modelshaderobs00_bxnxx", 212, 4, 4, -1, -1, -1, -1, 12, -1, -1, 8, 16, -1, -1, -1, -1, 68, -1, -1, 20, -1, -1, -1, -1, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 100, 132, 116, -1, -1, 164, 196, 148, 180, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0x39], "modelshaderobs01_bxnxx", 212, 4, 4, -1, -1, -1, -1, 16, 8, -1, 12, -1, -1, -1, -1, -1, 68, -1, -1, 20, -1, -1, -1, -1, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 100, 132, 116, -1, -1, 164, 196, 148, 180, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0x3a], "modelshaderobs01_bunxx", 212, 4, 4, -1, -1, -1, -1, 16, 8, -1, 12, -1, -1, -1, -1, -1, 68, -1, -1, 20, -1, -1, -1, -1, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 100, 132, 116, -1, -1, 164, 196, 148, 180, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0x3b], "modelshaderetc00_bxxxx", 172, 2, 4, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, 28, -1, -1, 12, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 44, -1, -1, -1, -1, 60, 92, 76, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x3c], "modelshaderetc01_bxnxx", 212, 4, 4, -1, -1, -1, -1, 12, -1, -1, 8, 16, -1, -1, -1, -1, 68, -1, -1, 20, -1, -1, -1, -1, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 100, 132, 116, -1, -1, 164, 196, 148, 180, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0x3e], "modelshaderefs01_bxxxx", 272, 3, 4, -1, -1, -1, -1, 12, -1, 8, -1, -1, -1, 144, -1, 32, 80, -1, -1, 16, -1, -1, -1, -1, -1, 128, -1, -1, -1, -1, -1, -1, -1, -1, 96, 112, -1, -1, -1, 160, 192, 176, -1, -1, -1, -1, -1, -1, -1, -1, 48, 64, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x40], "modelshaderobs02_bxxxx", 196, 4, 4, -1, -1, -1, 16, 12, 8, -1, -1, -1, -1, -1, -1, -1, 36, -1, -1, 20, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 68, -1, 52, -1, -1, 84, 116, 100, -1, -1, 148, 180, 132, 164, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x41], "modelshaderobs03_bxxxx", 196, 4, 4, 8, -1, -1, -1, 16, 12, -1, -1, -1, -1, -1, -1, -1, 52, -1, -1, 20, -1, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 68, -1, -1, -1, -1, 84, 116, 100, -1, -1, 148, 180, 132, 164, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x42], "modelshaderobs04_bxxxx", 172, 2, 4, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, 28, -1, -1, 12, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 44, -1, -1, -1, -1, 60, 92, 76, -1, -1, 124, 156, 108, 140, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x43], "modelshaderpls00_bxnxx", 312, 5, 4, -1, -1, -1, -1, 12, -1, -1, 8, 16, 20, -1, -1, -1, 72, -1, -1, 24, -1, -1, -1, -1, 40, -1, -1, -1, -1, 184, 168, 152, -1, -1, 136, -1, -1, -1, -1, 200, 232, 216, -1, -1, 264, 296, 248, 280, -1, -1, -1, -1, -1, -1, 120, 104, 88, -1, -1, -1, -1, -1, -1, -1, -1, 56);
	bayoSetMatType(bayoMatTypes[0x44], "modelshaderpls01_bxxxx", 228, 4, 4, -1, -1, -1, -1, 8, -1, -1, -1, 12, 16, -1, -1, -1, 20, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 116, 148, 132, -1, -1, 180, 212, 164, 196, -1, -1, -1, -1, -1, 100, 68, 52, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x45], "modelshadermag00_xxxxx", 300, 2, 4, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, 28, -1, 108, -1, 12, -1, -1, -1, -1, 44, 156, 284, 76, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 204, 236, 220, -1, -1, -1, -1, -1, 268, -1, -1, -1, 92, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 140, 124, -1, 60);
	bayoSetMatType(bayoMatTypes[0x46], "modelshadermag00_bxxxx", 300, 2, 4, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, 28, -1, 108, -1, 12, -1, -1, -1, -1, 44, 156, 284, 76, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 204, 236, 220, -1, -1, -1, -1, -1, 268, -1, -1, -1, 92, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 140, 124, -1, 60);
	bayoSetMatType(bayoMatTypes[0x48], "modelshaderbgs01_bxxxx", 192, 3, 4, -1, -1, -1, -1, -1, 8, -1, 12, -1, -1, -1, -1, 32, -1, -1, -1, 16, -1, -1, -1, -1, 48, 80, 176, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 112, 144, 128, -1, -1, -1, -1, -1, 160, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 64);
	bayoSetMatType(bayoMatTypes[0x49], "modelshaderbgs02_bxxxx", 228, 4, 4, -1, -1, -1, -1, 16, 8, -1, 12, -1, -1, -1, -1, 36, 84, -1, -1, 20, -1, -1, -1, -1, 52, 116, 212, -1, -1, -1, -1, -1, -1, -1, 100, -1, -1, -1, -1, 148, 180, 164, -1, -1, -1, -1, -1, 196, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 68);
	bayoSetMatType(bayoMatTypes[0x4a], "modelshaderbgs04_bxxxx", 212, 4, 4, 8, -1, -1, -1, -1, 12, -1, 16, -1, -1, -1, -1, 52, -1, -1, -1, 20, -1, 36, -1, -1, 68, 100, 196, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 132, 164, 148, -1, -1, -1, -1, -1, 180, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84);
	bayoSetMatType(bayoMatTypes[0x4b], "modelshaderobs00_bxnmx", 212, 4, 4, -1, -1, -1, -1, 12, -1, -1, 8, 16, -1, -1, -1, -1, 68, -1, -1, 20, -1, -1, -1, -1, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 100, 132, 116, -1, -1, 164, 196, 148, 180, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0x4c], "modelshaderobs04_bxxmx", 172, 2, 4, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, 28, -1, -1, 12, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 44, -1, -1, -1, -1, 60, 92, 76, -1, -1, 124, 156, 108, 140, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x4d], "modelshaderobs05_bxxxx", 176, 3, 4, -1, -1, -1, -1, 8, -1, -1, -1, 12, -1, -1, -1, -1, 32, -1, -1, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 48, -1, -1, -1, -1, 64, 96, 80, -1, -1, 128, 160, 112, 144, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x4e], "modelshaderobs05_bxxmx", 176, 3, 4, -1, -1, -1, -1, 8, -1, -1, -1, 12, -1, -1, -1, -1, 32, -1, -1, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 48, -1, -1, -1, -1, 64, 96, 80, -1, -1, 128, 160, 112, 144, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x53], "modelshaderbgs00_bxxxx", 104, 1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 40, 72, 56, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x54], "modelshaderobs01_bxxxx", 212, 4, 4, -1, -1, -1, -1, 16, 8, -1, 12, -1, -1, -1, -1, -1, 68, -1, -1, 20, -1, -1, -1, -1, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 100, 132, 116, -1, -1, 164, 196, 148, 180, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0x55], "modelshaderobs06_bxxxx", 208, 3, 4, -1, -1, -1, -1, 12, -1, -1, 8, -1, -1, -1, -1, -1, 64, -1, -1, 16, -1, -1, -1, -1, 32, -1, -1, -1, -1, -1, -1, -1, -1, -1, 80, -1, -1, -1, -1, 96, 128, 112, -1, -1, 160, 192, 144, 176, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 48);
	bayoSetMatType(bayoMatTypes[0x56], "modelshaderobs06_bxxmx", 208, 3, 4, -1, -1, -1, -1, 12, -1, -1, 8, -1, -1, -1, -1, -1, 64, -1, -1, 16, -1, -1, -1, -1, 32, -1, -1, -1, -1, -1, -1, -1, -1, -1, 80, -1, -1, -1, -1, 96, 128, 112, -1, -1, 160, 192, 144, 176, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 48);
	bayoSetMatType(bayoMatTypes[0x57], "modelshadergrs00_xxxxx", 88, 1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 40, 24, -1, -1, -1, -1, -1, -1, -1, -1, 56, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x58], "modelshaderpls02_bxxxx", 120, 1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 56, -1, 24, -1, -1, -1, 8, -1, -1, -1, -1, -1, 40, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 72, 104, 88, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x59], "modelshaderobs01_bxxmx", 212, 4, 4, -1, -1, -1, -1, 16, 8, -1, 12, -1, -1, -1, -1, -1, 68, -1, -1, 20, -1, -1, -1, -1, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 100, 132, 116, -1, -1, 164, 196, 148, 180, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0x5a], "modelshaderefs00_xxxxx", 120, 1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 56, -1, 24, -1, -1, -1, 8, -1, -1, -1, -1, -1, 40, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 72, 104, 88, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x5b], "modelshaderobs01_buxmx", 212, 4, 4, -1, -1, -1, -1, 16, 8, -1, 12, -1, -1, -1, -1, -1, 68, -1, -1, 20, -1, -1, -1, -1, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 100, 132, 116, -1, -1, 164, 196, 148, 180, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0x5c], "modelshaderobs01_bunmx", 212, 4, 4, -1, -1, -1, -1, 16, 8, -1, 12, -1, -1, -1, -1, -1, 68, -1, -1, 20, -1, -1, -1, -1, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 100, 132, 116, -1, -1, 164, 196, 148, 180, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0x5d], "modelshaderobs03_bxxmx", 196, 4, 4, 8, -1, -1, -1, 16, 12, -1, -1, -1, -1, -1, -1, -1, 52, -1, -1, 20, -1, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 68, -1, -1, -1, -1, 84, 116, 100, -1, -1, 148, 180, 132, 164, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x61], "modelshaderbgs05_bxxxx", 248, 5, 4, 8, -1, -1, -1, 20, 12, -1, 16, -1, -1, -1, -1, 56, 104, -1, -1, 24, -1, 40, -1, -1, 72, 136, 232, -1, -1, -1, -1, -1, -1, -1, 120, -1, -1, -1, -1, 168, 200, 184, -1, -1, -1, -1, -1, 216, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 88);
	bayoSetMatType(bayoMatTypes[0x62], "modelshadergrs00_bxxxx", 88, 1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 40, 24, -1, -1, -1, -1, -1, -1, -1, -1, 56, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x68], "modelshaderetc00_bxxmx", 172, 2, 4, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, 28, -1, -1, 12, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 44, -1, -1, -1, -1, 60, 92, 76, -1, -1, 124, 156, 108, 140, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x6a], "modelshaderefs04_bxnxx", 212, 4, 4, -1, -1, 16, -1, 12, -1, -1, 8, -1, -1, -1, -1, -1, 68, -1, -1, 20, -1, -1, -1, -1, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 100, 132, 116, -1, -1, 164, 196, 148, 180, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0x6b], "modelshaderobs07_bxnxx", 208, 3, 4, -1, -1, -1, -1, 12, -1, -1, 8, -1, -1, -1, -1, -1, 64, -1, -1, 16, -1, -1, -1, -1, 32, -1, -1, -1, -1, -1, -1, -1, -1, -1, 80, -1, -1, -1, -1, 96, 128, 112, -1, -1, 160, 192, 144, 176, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 48);
	bayoSetMatType(bayoMatTypes[0x6c], "modelshaderefs05_bxxxx", 176, 3, 4, -1, -1, 12, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, 32, -1, -1, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 48, -1, -1, -1, -1, 64, 96, 80, -1, -1, 128, 160, 112, 144, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x6d], "modelshaderobs07_bxnmx", 208, 3, 4, -1, -1, -1, -1, 12, -1, -1, 8, -1, -1, -1, -1, -1, 64, -1, -1, 16, -1, -1, -1, -1, 32, -1, -1, -1, -1, -1, -1, -1, -1, -1, 80, -1, -1, -1, -1, 96, 128, 112, -1, -1, 160, 192, 144, 176, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 48);
	bayoSetMatType(bayoMatTypes[0x6e], "modelshaderpls03_bxnxx", 212, 4, 4, -1, -1, -1, 16, 12, -1, -1, 8, -1, -1, -1, -1, -1, 68, -1, -1, 20, -1, -1, -1, -1, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 100, 132, 116, -1, -1, 164, 196, 148, 180, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0x71], "modelshaderpls01_bxxmx", 228, 4, 4, -1, -1, -1, -1, 8, -1, -1, -1, 12, 16, -1, -1, -1, 20, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 116, 148, 132, -1, -1, 180, 212, 164, 196, -1, -1, -1, -1, -1, 100, 68, 52, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x72], "modelshaderpls04_bxnxx", 212, 4, 4, -1, -1, -1, 16, 12, -1, -1, 8, -1, -1, -1, -1, -1, 68, -1, -1, 20, -1, -1, -1, -1, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 100, 132, 116, -1, -1, 164, 196, 148, 180, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0x74], "modelshaderbgs09_xxxxx", 228, 4, 4, -1, -1, -1, -1, 16, 8, -1, 12, -1, -1, -1, -1, 36, 84, -1, -1, 20, -1, -1, -1, -1, 52, 116, 212, -1, -1, -1, -1, -1, -1, -1, 100, -1, -1, -1, -1, 148, 180, 164, -1, -1, -1, -1, -1, 196, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 68);
	bayoSetMatType(bayoMatTypes[0x75], "modelshadergls01_bxxxx", 172, 2, 4, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, 28, -1, -1, -1, -1, 44, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 60, 92, 76, 12, -1, 124, 156, 108, 140, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x76], "modelshaderbos02_bxnxx", 212, 4, 4, 8, -1, -1, -1, 16, -1, -1, 12, -1, -1, -1, -1, -1, 68, -1, -1, 20, -1, 36, -1, -1, 52, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 100, 132, 116, -1, -1, 164, 196, 148, 180, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x79], "modelshaderbos02_bxnmx", 212, 4, 4, 8, -1, -1, -1, 16, -1, -1, 12, -1, -1, -1, -1, -1, 68, -1, -1, 20, -1, 36, -1, -1, 52, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 100, 132, 116, -1, -1, 164, 196, 148, 180, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x7a], "modelshaderbgs07_bxxxx", 356, 4, 4, -1, -1, 16, -1, 12, 8, -1, -1, -1, -1, -1, -1, 36, 84, 164, -1, 20, -1, -1, -1, -1, 52, 212, 340, 100, -1, -1, -1, -1, -1, -1, -1, 132, -1, -1, -1, 260, 292, 276, -1, -1, -1, -1, -1, 324, -1, -1, -1, 116, 148, -1, -1, -1, -1, -1, -1, -1, -1, -1, 196, 180, -1, 68);
	bayoSetMatType(bayoMatTypes[0x7c], "modelshaderbgs09_bxxxx", 228, 4, 4, -1, -1, -1, -1, 16, 8, -1, 12, -1, -1, -1, -1, 36, 84, -1, -1, 20, -1, -1, -1, -1, 52, 116, 212, -1, -1, -1, -1, -1, -1, -1, 100, -1, -1, -1, -1, 148, 180, 164, -1, -1, -1, -1, -1, 196, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 68);
	bayoSetMatType(bayoMatTypes[0x7d], "modelshaderetc02_bxxmx", 108, 2, 4, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, 28, -1, -1, 12, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 44, -1, -1, -1, -1, 60, 92, 76, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x7f], "modelshaderpls05_bxnxx", 292, 4, 4, -1, -1, -1, -1, 12, -1, -1, 8, -1, 16, -1, -1, -1, 68, -1, -1, 20, -1, -1, -1, -1, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, 148, -1, -1, -1, -1, 180, 212, 196, -1, -1, 244, 276, 228, 260, -1, -1, -1, -1, -1, 164, 132, 116, 84, 100, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0x80], "modelshaderobs09_bxxmx", 192, 3, 4, -1, -1, -1, -1, 12, 8, -1, -1, -1, -1, -1, -1, -1, 48, -1, -1, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 64, -1, -1, -1, -1, 80, 112, 96, -1, -1, 144, 176, 128, 160, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x81], "modelshadergls03_bxxxx", 288, 3, 4, -1, -1, -1, -1, 12, -1, 8, -1, -1, -1, 160, -1, 32, 96, -1, -1, 16, -1, -1, -1, -1, -1, 144, -1, -1, -1, -1, -1, -1, -1, -1, 112, 128, -1, 80, -1, 176, 208, 192, -1, -1, -1, -1, -1, -1, -1, -1, 48, 64, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x82], "modelshadergls02_xxxxx", 172, 2, 4, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, 28, -1, -1, -1, -1, 44, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 60, 92, 76, 12, -1, 124, 156, 108, 140, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x83], "modelshadergls01_bxxxx", 172, 2, 4, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, 28, -1, -1, -1, -1, 44, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 60, 92, 76, 12, -1, 124, 156, 108, 140, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x84], "modelshaderpls01_bxxxa", 228, 4, 4, -1, -1, -1, -1, 8, -1, -1, -1, 12, 16, -1, -1, -1, 20, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 116, 148, 132, -1, -1, 180, 212, 164, 196, -1, -1, -1, -1, -1, 100, 68, 52, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x87], "modelshaderpls06_bxnxx", 212, 4, 4, -1, -1, -1, 16, 12, -1, -1, 8, -1, -1, -1, -1, -1, 68, -1, -1, 20, -1, -1, -1, -1, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 100, 132, 116, -1, -1, 164, 196, 148, 180, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0x88], "modelshaderbgs03_xxxxx", 192, 3, 4, -1, -1, -1, -1, 12, 8, -1, -1, -1, -1, -1, -1, -1, 48, -1, -1, 16, -1, -1, -1, -1, -1, 80, 176, -1, -1, -1, -1, -1, -1, -1, 64, -1, -1, -1, -1, 112, 144, 128, -1, -1, -1, -1, -1, 160, -1, 32, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x89], "modelshaderbgs03_bxxxx", 192, 3, 4, -1, -1, -1, -1, 12, 8, -1, -1, -1, -1, -1, -1, -1, 48, -1, -1, 16, -1, -1, -1, -1, -1, 80, 176, -1, -1, -1, -1, -1, -1, -1, 64, -1, -1, -1, -1, 112, 144, 128, -1, -1, -1, -1, -1, 160, -1, 32, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x8d], "modelshaderbgs11_xxxxx", 212, 4, 4, -1, -1, -1, -1, 16, 8, -1, 12, -1, -1, -1, -1, -1, -1, -1, -1, 20, -1, -1, -1, -1, 36, 100, 196, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 132, 164, 148, -1, -1, -1, -1, -1, 180, -1, 68, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0x8e], "modelshaderbgs12_xxxxx", 212, 4, 4, -1, -1, -1, -1, 16, 8, -1, 12, -1, -1, -1, -1, -1, -1, -1, -1, 20, -1, -1, -1, -1, 36, 100, 196, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 132, 164, 148, -1, -1, -1, -1, -1, 180, -1, 68, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0x8f], "modelshaderbgs11_bxxxx", 212, 4, 4, -1, -1, -1, -1, 16, 8, -1, 12, -1, -1, -1, -1, -1, -1, -1, -1, 20, -1, -1, -1, -1, 36, 100, 196, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 132, 164, 148, -1, -1, -1, -1, -1, 180, -1, 68, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0x91], "modelshaderbgs12_bxxxx", 212, 4, 4, -1, -1, -1, -1, 16, 8, -1, 12, -1, -1, -1, -1, -1, -1, -1, -1, 20, -1, -1, -1, -1, 36, 100, 196, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 132, 164, 148, -1, -1, -1, -1, -1, 180, -1, 68, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0x92], "modelshaderbgs14_bxxxx", 156, 2, 4, -1, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, 28, -1, -1, -1, 12, -1, -1, -1, -1, -1, 44, 140, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 76, 108, 92, -1, -1, -1, -1, -1, 124, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x93], "modelshaderbgs14_xxxxx", 156, 2, 4, -1, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, 28, -1, -1, -1, 12, -1, -1, -1, -1, -1, 44, 140, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 76, 108, 92, -1, -1, -1, -1, -1, 124, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x94], "modelshaderpls07_bxxxa", 228, 4, 4, -1, -1, -1, -1, 8, -1, -1, -1, 12, 16, -1, -1, -1, 20, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 116, 148, 132, -1, -1, 180, 212, 164, 196, -1, -1, -1, -1, -1, 100, 68, 52, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x96], "modelshaderetc03_bxxxx", 104, 1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 40, 72, 56, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x97], "modelshaderpls09_bxxmx", 276, 4, 4, -1, -1, -1, 16, 8, -1, -1, -1, -1, 12, -1, -1, -1, 20, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 132, -1, 36, -1, -1, 164, 196, 180, -1, -1, 228, 260, 212, 244, -1, -1, -1, -1, -1, -1, 116, 100, 52, 68, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x9c], "modelshaderetc04_xxxxx", 156, 2, 4, -1, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 12, -1, -1, -1, -1, -1, 28, 140, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 76, 108, 92, -1, 44, -1, -1, -1, 124, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x9d], "modelshaderetc05_xxxxx", 88, 1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 40, 72, 56, -1, 24, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x9e], "modelshaderetc04_bxxxx", 156, 2, 4, -1, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 12, -1, -1, -1, -1, -1, 28, 140, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 76, 108, 92, -1, 44, -1, -1, -1, 124, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x9f], "modelshaderetc05_bxxxx", 88, 1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 40, 72, 56, -1, 24, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0xa1], "modelshaderetc06_bxxxx", 176, 3, 4, -1, -1, -1, -1, 8, -1, -1, -1, 12, -1, -1, -1, -1, 32, -1, -1, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 48, -1, -1, -1, -1, 64, 96, 80, -1, -1, 128, 160, 112, 144, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0xa3], "modelshaderobs10_bxnxx", 228, 4, 4, -1, -1, -1, 16, 12, -1, -1, 8, -1, -1, -1, -1, -1, 68, -1, -1, 20, -1, -1, -1, -1, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, 100, -1, 84, -1, -1, 116, 148, 132, -1, -1, 180, 212, 164, 196, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0xa4], "modelshaderetc06_bxxmx", 176, 3, 4, -1, -1, -1, -1, 8, -1, -1, -1, 12, -1, -1, -1, -1, 32, -1, -1, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 48, -1, -1, -1, -1, 64, 96, 80, -1, -1, 128, 160, 112, 144, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0xaa], "modelshaderetc07_bxxxx", 196, 4, 4, -1, -1, -1, 16, 12, 8, -1, -1, -1, -1, -1, -1, -1, 36, -1, -1, 20, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 68, -1, 52, -1, -1, 84, 116, 100, -1, -1, 148, 180, 132, 164, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0xac], "modelshaderobs07_bxnxa", 208, 3, 4, -1, -1, -1, -1, 12, -1, -1, 8, -1, -1, -1, -1, -1, 64, -1, -1, 16, -1, -1, -1, -1, 32, -1, -1, -1, -1, -1, -1, -1, -1, -1, 80, -1, -1, -1, -1, 96, 128, 112, -1, -1, 160, 192, 144, 176, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 48);
	bayoSetMatType(bayoMatTypes[0xae], "modelshaderetc08_bxxmx", 172, 2, 4, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, 28, -1, -1, 12, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 44, -1, -1, -1, -1, 60, 92, 76, -1, -1, 124, 156, 108, 140, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0xb1], "modelshaderetc10_bxxxx", 188, 2, 4, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, 28, 44, -1, -1, 12, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 108, 140, 124, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0xb2], "modelshaderpls03_bxnxa", 212, 4, 4, -1, -1, -1, 16, 12, -1, -1, 8, -1, -1, -1, -1, -1, 68, -1, -1, 20, -1, -1, -1, -1, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 100, 132, 116, -1, -1, 164, 196, 148, 180, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0xb3], "modelshaderpls05_bxnxa", 292, 4, 4, -1, -1, -1, -1, 12, -1, -1, 8, -1, 16, -1, -1, -1, 68, -1, -1, 20, -1, -1, -1, -1, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, 148, -1, -1, -1, -1, 180, 212, 196, -1, -1, 244, 276, 228, 260, -1, -1, -1, -1, -1, 164, 132, 116, 84, 100, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0xb6], "modelshaderpls01_bxxma", 228, 4, 4, -1, -1, -1, -1, 8, -1, -1, -1, 12, 16, -1, -1, -1, 20, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 116, 148, 132, -1, -1, 180, 212, 164, 196, -1, -1, -1, -1, -1, 100, 68, 52, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0xb7], "modelshaderobs07_bxnma", 208, 3, 4, -1, -1, -1, -1, 12, -1, -1, 8, -1, -1, -1, -1, -1, 64, -1, -1, 16, -1, -1, -1, -1, 32, -1, -1, -1, -1, -1, -1, -1, -1, -1, 80, -1, -1, -1, -1, 96, 128, 112, -1, -1, 160, 192, 144, 176, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 48);
	bayoSetMatType(bayoMatTypes[0xbb], "modelshaderpls05_bxnxb", 292, 4, 4, -1, -1, -1, -1, 12, -1, -1, 8, -1, 16, -1, -1, -1, 68, -1, -1, 20, -1, -1, -1, -1, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, 148, -1, -1, -1, -1, 180, 212, 196, -1, -1, 244, 276, 228, 260, -1, -1, -1, -1, -1, 164, 132, 116, 84, 100, -1, -1, -1, -1, -1, -1, -1, 52);
	bayoSetMatType(bayoMatTypes[0xbc], "modelshaderpls01_bxxxz", 228, 4, 4, -1, -1, -1, -1, 8, -1, -1, -1, 12, 16, -1, -1, -1, 20, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, 116, 148, 132, -1, -1, 180, 212, 164, 196, -1, -1, -1, -1, -1, 100, 68, 52, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1);
}
