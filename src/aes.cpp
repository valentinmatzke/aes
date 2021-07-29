#include "aes.h"

AES::AES(int size, std::string inputFile, std::string outputFile)
{
  this->size = size;
  this->inputFile = inputFile;

  switch (this->size)
  {
  case 128:
  case 192:
  case 265:
    break;
  default:
    this->size = 128;
    break;
  }

  if (this->inputFile.compare(""))
  {
    this->inputFile = "input.txt";
  }

  if (this->outputFile.compare(""))
  {
    this->outputFile = "output.txt";
  }
}

void AES::encrypt()
{
  const int rows = 4;
  const int columns = size / 32;

  this->generate_cipher_key();

  std::ifstream inFile(this->inputFile, std::ios::in | std::ios::binary);
  std::ofstream outFile(this->outputFile, std::ios::out | std::ios::binary);

  while (1)
  {
    std::vector<uint8_t> nBytes = this->get_size_bytes_from_file(inFile);

    if (nBytes.empty())
    {
      break;
    }
    this->perform_encryption(outFile, nBytes);
  }

  inFile.close();
  outFile.close();
}

void AES::decrypt()
{
}

int AES::get_size()
{
  return this->size;
}

std::vector<uint8_t> AES::get_cipher_key()
{
  return this->cipherKey;
}

void AES::generate_cipher_key()
{
  int sizeInBytes = this->size / 8;

  this->cipherKey.resize(sizeInBytes);

  std::generate(begin(this->cipherKey), end(this->cipherKey), std::ref(this->rbe));
}

std::vector<uint8_t> AES::get_size_bytes_from_file(std::ifstream &inFile)
{
  int sizeInBytes = this->size / 8;

  std::vector<uint8_t> nBytes(sizeInBytes);

  return nBytes;

}

void AES::perform_encryption(std::ofstream &outFile, std::vector<uint8_t> nBytes)
{
}