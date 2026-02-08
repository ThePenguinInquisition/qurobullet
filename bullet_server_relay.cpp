#include "bullet_server_relay.h"

void BulletServerRelay::spawn_bullet( const Vector2 &p_position,  const Ref<BulletPath> &p_path, 
		const Ref<BulletTexture> &p_texture, const Dictionary &p_custom_data) {
	emit_signal("bullet_spawn_requested", p_position, p_path, p_texture, p_custom_data);
}

void BulletServerRelay::spawn_volley(const Vector2 &p_origin, const Array &p_shots,
		const Ref<BulletTexture> &p_texture, const Dictionary &p_custom_data) {
	emit_signal("volley_spawn_requested", p_origin, p_shots, p_texture, p_custom_data);
}

void BulletServerRelay::_bind_methods() {
	ClassDB::bind_method(D_METHOD("spawn_bullet", "position", "path", "texture", "custom_data"), &BulletServerRelay::spawn_bullet);
	ADD_SIGNAL(MethodInfo("bullet_spawn_requested",  
			PropertyInfo(Variant::VECTOR2, "position"),
			PropertyInfo(Variant::OBJECT, "path", PROPERTY_HINT_RESOURCE_TYPE, "BulletPath"), 
			PropertyInfo(Variant::OBJECT, "texture", PROPERTY_HINT_RESOURCE_TYPE, "BulletTexture"), 
			PropertyInfo(Variant::DICTIONARY, "custom_data")
	));

	ClassDB::bind_method(D_METHOD("spawn_volley", "origin", "shots", "texture", "custom_data"), &BulletServerRelay::spawn_volley);
	ADD_SIGNAL(MethodInfo("volley_spawn_requested", 
			PropertyInfo(Variant::VECTOR2, "origin"), 
			PropertyInfo(Variant::ARRAY, "shots"), 
			PropertyInfo(Variant::OBJECT, "texture", PROPERTY_HINT_RESOURCE_TYPE, "BulletTexture"), 
			PropertyInfo(Variant::DICTIONARY, "custom_data")
	));
}

BulletServerRelay::BulletServerRelay() {
}

BulletServerRelay::~BulletServerRelay() {
}
