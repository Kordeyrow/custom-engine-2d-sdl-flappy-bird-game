#pragma once
#include <vector>
#include <set>
#include "IFixedUpdate.h"

class PhysicsSystem {

private:
	const float gravity = 9.8;
	const float world_space_proportion = 7;
	const float max_chained_simulation_count = 3;
	const float simulation_delay_seconds = 0.02;

	std::set<IFixedUpdate*> IFixedUpdate_list;

public:

	void init() {
		//IFixedUpdate_list.reserve(10);
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
		for (auto obj : IFixedUpdate_list) {
			obj->currentForce.y += fixed_update_gravity;
			obj->get_transform()->position += obj->currentForce * interpolate_count * simulation_delay_seconds * world_space_proportion;
		}
	}

	void add(IFixedUpdate* obj) {
		//IFixedUpdate_list.push_back(obj);
		IFixedUpdate_list.insert(obj);
	}

	void remove(IFixedUpdate* obj) {
		IFixedUpdate_list.erase(obj);
		/*auto id = std::find(IFixedUpdate_list.begin(), IFixedUpdate_list.end(), obj);
		if (id != IFixedUpdate_list.end()) {
			IFixedUpdate_list.erase(id);
		}*/
	}
};

