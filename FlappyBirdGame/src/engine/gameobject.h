#pragma once
#include <vector>

class Component {

};

class Gameobject {
	int _id;
	static int next_id;
	std::vector<Component> components;

public:
	/*template<typename DerivedComponent>
	typename std::enable_if<std::is_base_of<Component, DerivedComponent>::value, DerivedComponent*>::type*/

	/*template < typename DerivedComponent,
		class std::enable_if < !std::is_integral<DerivedComponent>::value, int >::type = 0 >
	DerivedComponent* get_component() {
		for (auto& comp : components) {
			auto derivedComponent = get_derived_type<DerivedComponent>(comp);
			if (derivedComponent) {
				return derivedComponent;
			}
		}
		return nullptr;
	}*/

	template<typename DerivedComponent>
	DerivedComponent* get_component() {
		// Ensure that DerivedComponent is derived from Component
		static_assert(std::is_base_of<Component, DerivedComponent>::value, "DerivedComponent must be derived from Component");

		for (auto& comp : components) {
			if (auto* derivedComponent = dynamic_cast<DerivedComponent*>(comp)) {
				return derivedComponent;
			}
		}
		return nullptr; 
	}

	template<typename DerivedComponent>
	typename std::enable_if<std::is_base_of<Component, DerivedComponent>::value, std::vector<Component*>&>::type
	get_components() {
		std::vector<Component*>& found_components{};
		for (auto& comp : components) {
			auto derivedComponent = get_derived_type<DerivedComponent>(comp);
			if (derivedComponent) {
				found_components.insert(derivedComponent);
			}
		}
		return found_components;
	}

	template<typename DerivedComponent, typename... Args>
	DerivedComponent* add_component(Args&&... args) {
		// Compile-time check: Ensure DerivedComponent is derived from Component
		static_assert(std::is_base_of<Component, DerivedComponent>::value,
			"DerivedComponent must be derived from Component");

		// Compile-time check: Ensure DerivedComponent is constructible with given arguments
		static_assert(std::is_constructible<DerivedComponent, Args...>::value,
			"DerivedComponent cannot be constructed with the given arguments");

		// If checks pass, create the new component
		auto* newComponent = new DerivedComponent(std::forward<Args>(args)...);

		// Store in component list
		components.push_back(newComponent);

		return newComponent;
	}

	template<typename DerivedComponent>
	DerivedComponent* get_derived_type(Component* component) {
		return dynamic_cast<const DerivedComponent*>(&component);
	}

	const Transform transform;

	Gameobject() : _id(next_id++) { }
	int id() const { return _id; };
};

using GameobjectID = size_t;

