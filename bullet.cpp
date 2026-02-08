#include "bullet.h"

#include "core/os/time.h"

void Bullet::pop() {
	state = Bullet::POPPED_REQUESTED;
	RS::get_singleton()->canvas_item_set_visible(ci_rid, false);
}

bool Bullet::is_popped() {
	return state != Bullet::LIVE;
}

Bullet::State Bullet::get_state() {
	return state;
}

bool Bullet::can_collide() {
	return !is_popped() && texture.is_valid() && !texture->get_collision_shape().is_null() && texture->get_collision_mask() != 0;
}

float Bullet::get_age() const {
	return (Time::get_singleton()->get_ticks_msec() - spawntime)/1000.0;
}

float Bullet::get_path_time() const {
	return (Time::get_singleton()->get_ticks_msec() - path_start)/1000.0;
}

void Bullet::set_texture(const Ref<BulletTexture> &p_texture) {
	ERR_FAIL_COND_MSG(!p_texture.is_valid(), "Passed BulletTexture is invalid. Cannot update.");

	texture = p_texture;

	RenderingServer *rs = RS::get_singleton();
	Ref<Texture2D> sprite = p_texture->get_texture();

	rs->canvas_item_clear(ci_rid);

	ERR_FAIL_COND_MSG(!sprite.is_valid(), "Passed BulletTexture has no Texture2D. Cannot render.");

	sprite->draw(ci_rid, -sprite->get_size()/2);

	if (p_texture->get_material().is_valid()) {
		rs->canvas_item_set_material(ci_rid, p_texture->get_material()->get_rid());
	}
	
	rs->canvas_item_set_modulate(ci_rid, p_texture->get_modulate());
	rs->canvas_item_set_light_mask(ci_rid, p_texture->get_light_mask());
}

Ref<BulletTexture> Bullet::get_texture() const {
	return texture;
}

void Bullet::set_path(const Ref<BulletPath> &p_path) {
	ERR_FAIL_COND_MSG(!p_path.is_valid(), "Passed BulletPath is invalid. Cannot update.");
	path = p_path;
	path_start = Time::get_singleton()->get_ticks_msec();
}

Ref<BulletPath> Bullet::get_path() const {
	return path;
}

void Bullet::set_position(const Vector2 &p_position) {
	transform.set_origin(p_position);
}

Vector2 Bullet::get_position() const {
	return transform.get_origin();
}

Vector2 Bullet::get_direction() const {
	ERR_FAIL_COND_V_MSG(!path.is_valid(), Vector2(0,0), "Current path is invalid. Cannot return direction on invalid path.");
	return path->get_direction(get_age());
}

Vector2 Bullet::get_velocity() const {
	ERR_FAIL_COND_V_MSG(!path.is_valid(), Vector2(0,0), "Current path is invalid. Cannot return velocity on invalid path.");
	return path->get_velocity(get_age());
}

float Bullet::get_rotation() const {
	ERR_FAIL_COND_V_MSG(!path.is_valid(), 0, "Current path is invalid. Cannot return rotation on invalid path.");
	return path->get_rotation(get_age());
}

float Bullet::get_speed() const {
	ERR_FAIL_COND_V_MSG(!path.is_valid(), 0, "Current path is invalid. Cannot return speed on invalid path.");
	return path->get_speed(get_age());
}

Transform2D Bullet::get_transform() const {
	return transform;
}

void Bullet::set_ci_rid(const RID &p_rid) {
	ci_rid = p_rid;
}

RID Bullet::get_ci_rid() const {
	return ci_rid;
}

void Bullet::set_custom_data(const Dictionary &p_custom_data) {
	custom_data = p_custom_data;
}

Dictionary Bullet::get_custom_data() const {
	return custom_data;
}

void Bullet::_bind_methods() {
	ClassDB::bind_method(D_METHOD("pop"), &Bullet::pop);
	ClassDB::bind_method(D_METHOD("is_popped"), &Bullet::is_popped);

	ClassDB::bind_method(D_METHOD("can_collide"), &Bullet::can_collide);

	ClassDB::bind_method(D_METHOD("get_age"), &Bullet::get_age);

	ClassDB::bind_method(D_METHOD("set_texture", "texture"), &Bullet::set_texture);
	ClassDB::bind_method(D_METHOD("get_texture"), &Bullet::get_texture);

	ClassDB::bind_method(D_METHOD("set_path", "path"), &Bullet::set_path);
	ClassDB::bind_method(D_METHOD("get_path"), &Bullet::get_path);

	ClassDB::bind_method(D_METHOD("set_position", "position"), &Bullet::set_position);
	ClassDB::bind_method(D_METHOD("get_position"), &Bullet::get_position);

	ClassDB::bind_method(D_METHOD("get_direction"), &Bullet::get_direction);
	ClassDB::bind_method(D_METHOD("get_velocity"), &Bullet::get_velocity);
	ClassDB::bind_method(D_METHOD("get_rotation"), &Bullet::get_rotation);
	ClassDB::bind_method(D_METHOD("get_speed"), &Bullet::get_speed);

	ClassDB::bind_method(D_METHOD("get_transform"), &Bullet::get_transform);

	ClassDB::bind_method(D_METHOD("get_ci_rid"), &Bullet::get_ci_rid);

	ClassDB::bind_method(D_METHOD("set_custom_data", "data"), &Bullet::set_custom_data);
	ClassDB::bind_method(D_METHOD("get_custom_data"), &Bullet::get_custom_data);

	BIND_ENUM_CONSTANT(LIVE);
	BIND_ENUM_CONSTANT(UNINITIALIZED);
	BIND_ENUM_CONSTANT(POPPED_OUT_OF_BOUNDS);
	BIND_ENUM_CONSTANT(POPPED_LIFETIME_SERVER);
	BIND_ENUM_CONSTANT(POPPED_LIFETIME_BULLET);
	BIND_ENUM_CONSTANT(POPPED_COLLIDE);
	BIND_ENUM_CONSTANT(POPPED_REQUESTED);
}

Bullet::Bullet() {
	ci_rid = RS::get_singleton()->canvas_item_create();
	transform = Transform2D();
	texture = Ref<BulletTexture>();
	path = Ref<BulletPath>();
	custom_data = Dictionary();
	state = Bullet::UNINITIALIZED;
	spawntime = 0;
}

Bullet::~Bullet() {
	RS::get_singleton()->free(ci_rid);
}
