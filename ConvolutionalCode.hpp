#include <stdint.h>
#include <vector>

class ConvolutionalCode {
  public:
     using bitvec_t = uint32_t;

     struct MemoryState {
         std::vector<bitvec_t> state_per_input_;
     };

     struct Generator {
	 std::vector<bitvec_t> generator_per_input_;
	 Generator(const std::vector<bitvec_t> &generator_per_input)
             : generator_per_input_(generator_per_input) {}
     };

     ConvolutionalCode(uint32_t k, uint32_t n, std::vector<uint32_t> m);
     void AddGenerator(const std::vector<bitvec_t> &state_per_input);
     bitvec_t GenerateOutput(bitvec_t input, MemoryState curr_state,
         MemoryState *next_state_ptr) const;

   private:
     const uint32_t k_ = 0;
     const uint32_t n_ = 0;
     const std::vector<uint32_t> m_;
     std::vector<Generator> generators_;
};
