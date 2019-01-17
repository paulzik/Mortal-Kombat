#pragma once
#include <list>
#include <set>

namespace input {

	using key_combination = std::list<int32_t>;

	extern bool test_key(int32_t, key_combination);

	inline bool test_keys(const key_combination& keys, key_combination _buttons) {
		int count = 0;
		for (auto& key : keys)
			if (test_key(key, _buttons))
				count++;
		return count == _buttons.size() && count > 0 && _buttons.size() == keys.size();
	}

	class InputManager final {
	public:
		using Logical = std::set<std::string>;
	private:
		using Actions = std::list<std::pair<input::key_combination, std::string>>;
		using All = std::list<InputManager*>;
		Actions actions;
		Logical logical;
		static All all;		// TODO: define it in a cpp file!	
		void SetLogical(const std::string& id) { logical.insert(id); }

	public:
		std::list< int32_t > buttons;

		void AddAction(const input::key_combination& keys, const std::string& logical)
		{
			actions.push_back(std::make_pair(keys, logical));
		}
		void Handle(void) {
			logical.clear();
			for (auto& i : actions) {
				if (input::test_keys(i.first, buttons))
					SetLogical(i.second);
			}

		}
		const Logical& GetLogical(void) const
		{
			return logical;
		}
		//static void HandleAll(void) {
		//	for (auto* handler : all)
		//		handler->Handle();
		//}

		InputManager(void) { /*all.push_back(this);*/ }
		~InputManager() { /*all.remove(this);*/ }
	};

} // input