#pragma once
#include <set>
#include "Rigidbody.h"

class PhysicsSystem {

private:
	const float gravity = -9.8;
	const float world_space_proportion = 9;
	const float max_chained_simulation_count = 3;
	const float simulation_delay_seconds = 0.02;
	const float air_resistance = 1.04;

	std::set<Rigidbody*> rigidbody_list;

	// Singleton
	PhysicsSystem() {
	}

public:

	// Static method to access the singleton instance
	static PhysicsSystem& GetInstance() {
		static PhysicsSystem instance;
		return instance;
	}

	// Prevent copying and assignment
	PhysicsSystem(const PhysicsSystem&) = delete;
	PhysicsSystem& operator=(const PhysicsSystem&) = delete;

	void init() {
		//Rigidbody_list.reserve(10);
	}

	float elapsed_time_sum = 0;
	void update(float elapsedTime) {
		elapsed_time_sum += elapsedTime;

		// base case 1
		if (elapsed_time_sum < simulation_delay_seconds) {
			return;
		}

		// base case 2
		elapsed_time_sum -= simulation_delay_seconds;
		run_simulation();
		if (elapsed_time_sum < simulation_delay_seconds) {
			return;
		}

		// edge case (big elapsedTime)
		int run_count = 1;
		while (elapsed_time_sum > simulation_delay_seconds) {
			if (run_count < max_chained_simulation_count) {
				elapsed_time_sum -= simulation_delay_seconds;
				run_simulation();
			}
			else {
				int interpolate_count = elapsed_time_sum / simulation_delay_seconds;
				elapsed_time_sum -= interpolate_count * simulation_delay_seconds;
				run_simulation(interpolate_count);
			}
			run_count++;
		}
	}

	void run_simulation(int interpolate_count = 1) {
		static float fixed_update_gravity = gravity * simulation_delay_seconds * world_space_proportion;
		for (auto& obj : rigidbody_list) {
			obj->final_force.y += fixed_update_gravity;
			auto fixed_update_final_force = obj->final_force * interpolate_count * simulation_delay_seconds * world_space_proportion;
			apply_force_movement(obj, fixed_update_final_force);
		}
	}

	void apply_force_movement(Rigidbody* obj, Vector2 finalForce) {
		finalForce.y *= -1;
		obj->gameobject->position += finalForce;

		// air_resistance
		obj->final_force.x /= air_resistance;
	}

	void add_force(Rigidbody* obj, Vector2 dir) {
		if (exists(obj)) {
			obj->final_force += dir;
		}
	}

	void reset_forces(Rigidbody* obj) {
		if (exists(obj)) {
			obj->final_force = Vector2::zero;
		}
	}

	bool exists(Rigidbody* obj) {
		return rigidbody_list.find(obj) != rigidbody_list.end();
	}

	void add(Rigidbody* obj) {
		//Rigidbody_list.push_back(obj);
		rigidbody_list.insert(obj);
	}

	void remove(Rigidbody* obj) {
		rigidbody_list.erase(obj);

		//Rigidbody_list.erase(obj);

		/*auto id = std::find(Rigidbody_list.begin(), Rigidbody_list.end(), obj);
		if (id != Rigidbody_list.end()) {
			Rigidbody_list.erase(id);
		}*/
	}
};

