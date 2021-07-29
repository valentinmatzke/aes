#include "aes.h"

AES::AES(int size, std::string inputFile)
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
}

void AES::encrypt()
{
  const int rows = 4;
  const int columns = size / 32;

}

void AES::decrypt()
{
}

int AES::get_size()
{
  return this->size;
}

std::vector<unsigned char> AES::get_cipher_key()
{
  return this->cipherKey;
}

void AES::generate_cipher_key()
{
  int sizeInBytes = this->size / 8;

  this->cipherKey.reserve(sizeInBytes);

  std::generate(begin(this->cipherKey), end(this->cipherKey), std::ref(this->rbe));
}