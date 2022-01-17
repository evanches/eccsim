#include <cassert>
#include "ConvolutionalCode.hpp"

ConvolutionalCode::ConvolutionalCode(uint32_t k, uint32_t n, std::vector<uint32_t> m)
    : k_(k), n_(n), m_(m) {
	assert(m_.size() == k);
}

void ConvolutionalCode::AddGenerator(const std::vector<bitvec_t> &state_per_input) {
    assert(state_per_input.size() == k_);
    for (size_t i = 0; i < state_per_input.size(); i++) {
        bitvec_t mask = (1U << m_.at(i)) - 1;
	assert((mask | state_per_input.at(i)) == mask);
    }
    generators_.push_back(Generator(state_per_input));
}

ConvolutionalCode::bitvec_t ConvolutionalCode::GenerateOutput(bitvec_t input,
       MemoryState curr_state, MemoryState* next_state_ptr) const {
    bitvec_t output = 0U;
    bitvec_t input_mask = (1 << k_) - 1;
    assert((input_mask | input) == input_mask);

    for (uint32_t o = 0; o < n_; o++) {
        const Generator& gen = generators_.at(o);
	uint32_t added_bits = 0;
	for (uint32_t i = 0; i < k_; i++) {
	    bitvec_t input_bit = (input >> i) & 1U;
	    bitvec_t state = curr_state.state_per_input_.at(i);
	    bitvec_t mask = (1U << m_[i]) - 1;
	    bitvec_t next_state = (input_bit | (state << 1)) & mask;

	    if (next_state_ptr && o == 0) {
		next_state_ptr->state_per_input_.at(i) = next_state;
	    }

	    bitvec_t addition = gen.generator_per_input_.at(i) & next_state;
	    added_bits += __builtin_popcount(addition);
	}
	output |= (added_bits % 2) << o;
    }

    return output;
}
