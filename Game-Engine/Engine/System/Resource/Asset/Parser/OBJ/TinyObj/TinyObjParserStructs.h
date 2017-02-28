#pragma once

#include <map>
#include <string>
#include <vector>

namespace TinyObj {

	typedef enum {
		TEXTURE_TYPE_NONE,  // default
		TEXTURE_TYPE_SPHERE,
		TEXTURE_TYPE_CUBE_TOP,
		TEXTURE_TYPE_CUBE_BOTTOM,
		TEXTURE_TYPE_CUBE_FRONT,
		TEXTURE_TYPE_CUBE_BACK,
		TEXTURE_TYPE_CUBE_LEFT,
		TEXTURE_TYPE_CUBE_RIGHT
	} texture_type_t;

	typedef struct {
		texture_type_t type;     // -type (default TEXTURE_TYPE_NONE)
		float sharpness;         // -boost (default 1.0?)
		float brightness;        // base_value in -mm option (default 0)
		float contrast;          // gain_value in -mm option (default 1)
		float origin_offset[3];  // -o u [v [w]] (default 0 0 0)
		float scale[3];          // -s u [v [w]] (default 1 1 1)
		float turbulence[3];     // -t u [v [w]] (default 0 0 0)
								 // int   texture_resolution; // -texres resolution (default = ?) TODO
		bool clamp;    // -clamp (default false)
		char imfchan;  // -imfchan (the default for bump is 'l' and for decal is 'm')
		bool blendu;   // -blendu (default on)
		bool blendv;   // -blendv (default on)
		float bump_multiplier;  // -bm (for bump maps only, default 1.0)
	} texture_option_t;

	typedef struct {
		std::string name;

		float ambient[3];
		float diffuse[3];
		float specular[3];
		float transmittance[3];
		float emission[3];
		float shininess;
		float ior;       // index of refraction
		float dissolve;  // 1 == opaque; 0 == fully transparent
						 // illumination model (see http://www.fileformat.info/format/material/)
		int illum;

		int dummy;  // Suppress padding warning.

		std::string ambient_texname;             // map_Ka
		std::string diffuse_texname;             // map_Kd
		std::string specular_texname;            // map_Ks
		std::string specular_highlight_texname;  // map_Ns
		std::string bump_texname;                // map_bump, bump
		std::string displacement_texname;        // disp
		std::string alpha_texname;               // map_d

		texture_option_t ambient_texopt;
		texture_option_t diffuse_texopt;
		texture_option_t specular_texopt;
		texture_option_t specular_highlight_texopt;
		texture_option_t bump_texopt;
		texture_option_t displacement_texopt;
		texture_option_t alpha_texopt;

		// PBR extension
		// http://exocortex.com/blog/extending_wavefront_mtl_to_support_pbr
		float roughness;            // [0, 1] default 0
		float metallic;             // [0, 1] default 0
		float sheen;                // [0, 1] default 0
		float clearcoat_thickness;  // [0, 1] default 0
		float clearcoat_roughness;  // [0, 1] default 0
		float anisotropy;           // aniso. [0, 1] default 0
		float anisotropy_rotation;  // anisor. [0, 1] default 0
		float pad0;
		float pad1;
		std::string roughness_texname;  // map_Pr
		std::string metallic_texname;   // map_Pm
		std::string sheen_texname;      // map_Ps
		std::string emissive_texname;   // map_Ke
		std::string normal_texname;     // norm. For normal mapping.

		texture_option_t roughness_texopt;
		texture_option_t metallic_texopt;
		texture_option_t sheen_texopt;
		texture_option_t emissive_texopt;
		texture_option_t normal_texopt;

		int pad2;

		std::map<std::string, std::string> unknown_parameter;
	} material_t;

	typedef struct {
		std::string name;

		std::vector<int> intValues;
		std::vector<float> floatValues;
		std::vector<std::string> stringValues;
	} tag_t;

	// Index struct to support different indices for vtx/normal/texcoord.
	// -1 means not used.
	typedef struct {
		int vertex_index;
		int normal_index;
		int texcoord_index;
	} index_t;

	typedef struct {
		std::vector<index_t> indices;
		std::vector<unsigned char> num_face_vertices;  // The number of vertices per
													   // face. 3 = polygon, 4 = quad,
													   // ... Up to 255.
		std::string materialName;
		std::vector<tag_t> tags;                       // SubD tag
	} mesh_t;

	typedef struct {
		std::string name;
		mesh_t mesh;
	} shape_t;

	// Vertex attributes
	typedef struct {
		std::vector<float> vertices;   // 'v'
		std::vector<float> normals;    // 'vn'
		std::vector<float> texcoords;  // 'vt'
	} attrib_t;

	typedef struct callback_t_ {
		// W is optional and set to 1 if there is no `w` item in `v` line
		void(*vertex_cb)(void *user_data, float x, float y, float z, float w);
		void(*normal_cb)(void *user_data, float x, float y, float z);

		// y and z are optional and set to 0 if there is no `y` and/or `z` item(s) in
		// `vt` line.
		void(*texcoord_cb)(void *user_data, float x, float y, float z);

		// called per 'f' line. num_indices is the number of face indices(e.g. 3 for
		// triangle, 4 for quad)
		// 0 will be passed for undefined index in index_t members.
		void(*index_cb)(void *user_data, index_t *indices, int num_indices);
		// `name` material name, `material_id` = the array index of material_t[]. -1
		// if
		// a material not found in .mtl
		void(*usemtl_cb)(void *user_data, const char *name, int material_id);
		// `materials` = parsed material data.
		void(*mtllib_cb)(void *user_data, const material_t *materials,
			int num_materials);
		// There may be multiple group names
		void(*group_cb)(void *user_data, const char **names, int num_names);
		void(*object_cb)(void *user_data, const char *name);

		callback_t_()
			: vertex_cb(NULL),
			normal_cb(NULL),
			texcoord_cb(NULL),
			index_cb(NULL),
			usemtl_cb(NULL),
			mtllib_cb(NULL),
			group_cb(NULL),
			object_cb(NULL) {}
	} callback_t;
}