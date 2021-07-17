#pragma once

namespace dust {
	struct BasicParticle {
		operator bool() const {	return this->alive;	}
		bool alive = false;
		float age = 0.0;
	};
};