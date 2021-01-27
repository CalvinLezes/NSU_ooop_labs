#include "tritset.h"

uint TritSet::get_empty() {
	uint empty = 1;
	for (int i = 0; i < sizeof(uint) * 4; i++) {
		empty <<= 2;
		empty |= 01;
	}
	return empty;
}

TritSet::TritSet() {
	origin_size = 1000;
	size = 1000;
	size_t array_size = static_cast<size_t>(ceil(ceil(size * 2 / 8) / sizeof(uint)));
	array = new uint[array_size];
	uint empty = get_empty();
	for (size_t i = 0; i < array_size; i++) {
		array[i] = empty;
	}
}
TritSet::TritSet(size_t capacity) {
	origin_size = capacity;
	size = capacity;
	size_t array_size = static_cast<size_t>(ceil(ceil(size * 2/ 8) / sizeof(uint)));
	array = new uint[array_size];
	uint empty = get_empty();
	for (size_t i = 0; i < array_size; i++) {
		array[i] = empty;
	}
}

TritSet::TritSet(TritSet& trit_set) {
	origin_size = trit_set.origin_size;
	size = trit_set.size;
	size_t array_size = static_cast<size_t>(ceil(ceil(size * 2 / 8) / sizeof(uint)));
	array = new uint[array_size];
	for (size_t i = 0; i < array_size; i++) {
		array[i] = trit_set.array[i];
	}
}

size_t TritSet::capacity() {
	return static_cast<size_t>(ceil(size * 2 / 8 / sizeof(uint)));
}

void TritSet::change_size(size_t new_size) {
	size_t array_size = capacity();
	size_t new_array_size = static_cast<size_t>(ceil(new_size * 2 / 8 / sizeof(uint)));
	uint* new_array = new uint[new_array_size];
	uint empty = get_empty();
	if (new_size <= size) {
		for (size_t i = 0; i < new_array_size; i++) {
			new_array[i] = array[i];
		}
	}
	else {
		for (size_t i = 0; i < array_size; i++) {
			new_array[i] = array[i];
		}
		for (size_t i = array_size; i < new_array_size; i++) {
			new_array[i] = empty;
		}
	}
	delete[] array;
	array = new_array;
	size = new_size;
}

void TritSet::shrink() {
	if (size < origin_size) {
		change_size(origin_size);
		return;
	}
	uint empty = get_empty();
	for (size_t i = capacity(); i > 0; i--) {
		if (array[i-1] != empty) {
			change_size(i * sizeof(uint) * 4);
			return;
		}
	}
	change_size(origin_size);
}

TritSet::Aproxy::Aproxy(TritSet& set, const uint ind) : trit_set{ set } {
	index = ind;
	position_in_uint = ind % (sizeof(uint) * 4);
	position_in_array = ind / (sizeof(uint) * 4);
}

TritSet::Aproxy& TritSet::Aproxy::operator= (Trit trit) {
	if (trit_set.capacity() < position_in_array) {
		if (trit == Trit::Unknown) {
			return *this;
		}
		else {
			trit_set.change_size(index);
		}
	}
	uint zero = 3;
	zero <<= (sizeof(uint) * 8 - position_in_uint * 2);
	zero = ~zero;
	trit_set.array[position_in_array] &= zero;
	switch (trit) {
	case Trit::Unknown: {
		trit_set.array[position_in_array] |= (1 << (sizeof(uint) * 8 - position_in_uint * 2));
		break;
	}
	case Trit::True: {
		trit_set.array[position_in_array] |= (2 << (sizeof(uint) * 8 - position_in_uint * 2));
		break;
	}
	case Trit::False: {
		trit_set.array[position_in_array] |= (0 << (sizeof(uint) * 8 - position_in_uint * 2));
		break;
	}
	default:
		break;
	}
	return *this;
}

bool TritSet::Aproxy::operator==(Trit trit) {
	if (trit_set.capacity() < position_in_array) {
		return false;
	}
	uint trit_to_check = trit_set.array[position_in_array];
	trit_to_check <<= (position_in_uint-1) * 2;
	trit_to_check >>= (sizeof(uint) * 8 - 2);
	uint comp_trit = static_cast<uint>(trit);
	return (comp_trit == trit_to_check);
}

bool TritSet::Aproxy::operator!=(Trit trit) {
	if (trit_set.capacity() < position_in_array) {
		return true;
	}
	uint trit_to_check = trit_set.array[position_in_array];
	trit_to_check <<= (position_in_uint - 1) * 2;
	trit_to_check >>= (sizeof(uint) * 8 - 2);
	uint comp_trit = static_cast<uint>(trit);
	return (comp_trit != trit_to_check);
}

TritSet::Aproxy TritSet::operator[](uint i) {
	return Aproxy((*this), i);
}

TritSet& TritSet::operator= (TritSet& trit_set) {
	origin_size = trit_set.origin_size;
	size = trit_set.size;
	delete[] array;
	size_t array_size = static_cast<size_t>(ceil(size * 2 / 8 / sizeof(uint)));
	array = new uint[array_size];
	for (size_t i = 0; i < array_size; i++) {
		array[i] = trit_set.array[i];
	}
	return *this;
}

bool TritSet::operator==(TritSet& trit_set) {
	if (size != trit_set.size) {
		return false;
	}
	for (size_t i = 0; i < capacity(); i++) {
		if (array[i] != trit_set.array[i]) {
			return false;
		}
	}
	return true;
}

bool TritSet::operator!=(TritSet& trit_set) {
	if (size != trit_set.size) {
		return true;
	}
	for (size_t i = 0; i < capacity(); i++) {
		if (array[i] != trit_set.array[i]) {
			return true;
		}
	}
	return false;
}

TritSet& TritSet::operator&(TritSet& setB) {
	if (size < setB.size) {
		change_size(setB.size);
	}
	for (size_t i = 0; i < capacity(); i++) {
		array[i] = array[i] & setB.array[i];
	}
	return (*this);
}

TritSet& TritSet::operator|(TritSet& setB) {
	if (size < setB.size) {
		change_size(setB.size);
	}
	for (size_t i = 0; i < capacity(); i++) {
		array[i] = array[i] | setB.array[i];
	}
	return (*this);
}

TritSet& TritSet::operator~() {
	for (size_t i = 0; i < size; i++) {
		if ((*this)[i] == Trit::True) {
			(*this)[i] = Trit::False;
		}
		else if ((*this)[i] == Trit::False) {
			(*this)[i] = Trit::True;
		}
	}
	return (*this);
}



size_t TritSet::cardinality(Trit value) {
	size_t count = 0;
	for (size_t i = 0; i < size; i++) {
		if ((*this)[i] == value) {
			count++;
		}
	}
	return count;
}

std::unordered_map < Trit, int, TritSet::tritHash > TritSet::cardinality() {
	unordered_map<Trit, int, TritSet::tritHash> cardinality_map;
	cardinality_map.insert(make_pair<Trit, int>(Trit::True, cardinality(Trit::True)));
	cardinality_map.insert(make_pair<Trit, int>(Trit::False, cardinality(Trit::False)));
	cardinality_map.insert(make_pair<Trit, int>(Trit::Unknown, cardinality(Trit::Unknown)));

	return cardinality_map;
}

void TritSet::trim(size_t lastIndex) {
	for (size_t i = lastIndex; i < size; i++) {
		if ((*this)[i] != Trit::Unknown) {
			(*this)[i] = Trit::Unknown;
		}
	}
};

size_t TritSet::length() {
	uint empty = get_empty();
	uint last=0;
	for (size_t i = capacity(); i >= 0; i--) {
		if (array[i] != empty) {
			last = i;
			break;
		}
	}
	for (size_t i = (last+1) * 4 * sizeof(uint) - 1; i > last * 4 * sizeof(uint); i--) {
		if ((*this)[i] != Trit::Unknown) {
			return i+1;
		}
	}
	return 1;
}