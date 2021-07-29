#include <string>
#include <vector>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>

class AES
{

public:
  void encrypt();
  void decrypt();
  int get_size();
  AES() = delete;
  AES(int size = 128, std::string inputFile = "input.txt");

private:
  int size;
  std::string inputFile;
  std::vector<unsigned char> cipherKey;
  std::independent_bits_engine<std::mt19937, CHAR_BIT, unsigned char> rbe;
  std::vector<unsigned char> get_cipher_key();
  void generate_cipher_key();
};