#pragma once
#include <unordered_map>
#include <cmath>
using namespace std;
using uint = unsigned int;

enum class Trit { False, Unknown, True };

class TritSet {
private:
	uint* array;
	size_t origin_size;
	size_t size;

	
public:

	TritSet();

	TritSet(size_t capacity);

	TritSet(TritSet& trit_set);

	~TritSet() {};

	size_t capacity();

	uint get_empty();

	void change_size(size_t new_size);

	void shrink();

	class Aproxy {
	private:
		TritSet& trit_set;
		uint index;
		uint position_in_uint;
		uint position_in_array;
	public:

		Aproxy(TritSet& set, const uint ind);

		Aproxy& operator= (Trit trit);
		bool operator== (Trit trit);
		bool operator!= (Trit trit);
	};

	Aproxy operator[](uint ind);

	TritSet& operator= (TritSet& trit_set);

	bool operator==(TritSet& trit_set);

	bool operator!=(TritSet& trit_set);

	TritSet& operator&(TritSet& setB);

	TritSet& operator|(TritSet& setB);

	TritSet& operator~();

	size_t cardinality(Trit value);

	typedef struct EnumClassHash
	{
		template <typename T>
		size_t operator()(T t) const
		{
			return static_cast<size_t>(t);
		}
	} tritHash;

	std::unordered_map < Trit, int, tritHash> cardinality();

	void trim(size_t lastIndex);

	size_t length();

};