#ifndef BULLETSERVERRELAY_H
#define BULLETSERVERRELAY_H

#include "resource/bullet_path.h"
#include "resource/bullet_texture.h"
#include "core/object/object.h"

class BulletServerRelay : public Object {
	GDCLASS(BulletServerRelay, Object);

protected:
	static void _bind_methods();

public:
	BulletServerRelay();
	~BulletServerRelay();

	void spawn_bullet(const Vector2 &p_position, const Ref<BulletPath> &p_path, const Ref<BulletTexture> &p_texture, const Dictionary &p_custom_data);
	void spawn_volley(const Vector2 &p_origin, const Array &p_shots, const Ref<BulletTexture> &p_texture, const Dictionary &p_custom_data);
};

#endif
