#pragma once

#include <stdint.h>
#include <stddef.h>

void
mi_vector_hash(const void * __restrict key, size_t len, uint32_t seed,
		uint32_t hashes[3]);
