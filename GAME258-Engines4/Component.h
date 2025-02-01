#pragma once
class Component {
	public:
		Component(Component* parent_) :parent(parent_), isCreated(false) {}
		virtual ~Component() = default; /// just means ~Component(){} either will work
		virtual bool OnCreate() = 0;
		virtual void OnDestroy() = 0;
		virtual void Update(const float deltaTime_) = 0;
		virtual void Render()const = 0;
	protected:
		Component* parent;
		/// Just a flag to indicate if the component or actor that inherits this 
		/// base class has called OnCreate (true) 
		bool isCreated;
};

