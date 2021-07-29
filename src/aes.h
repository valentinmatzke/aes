#include <string>
#include <vector>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>
#include <fstream>

class AES
{

public:
  void encrypt();
  void decrypt();
  int get_size();
  AES() = delete;
  AES(int size = 128, std::string inputFile = "input.txt", std::string outputFile = "output.txt");

private:
  int size;
  std::string inputFile;
  std::string outputFile;
  std::vector<uint8_t> cipherKey;
  std::independent_bits_engine<std::mt19937, CHAR_BIT, uint8_t> rbe;
  std::vector<uint8_t> get_cipher_key();
  void generate_cipher_key();
  std::vector<uint8_t> get_size_bytes_from_file(std::ifstream&);
  void perform_encryption(std::ofstream&, std::vector<uint8_t>);
};