#include "aes.h"
#include <iostream>

AES::AES(int size, std::string inputFile, std::string encryptedFile, std::string decryptedFile)
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

  if (this->encryptedFile.compare(""))
  {
    this->encryptedFile = "encrypted.txt";
  }

  if (this->decryptedFile.compare(""))
  {
    this->decryptedFile = "decrypted.txt";
  }
}

void AES::encrypt()
{
  const int rows = 4;
  const int columns = size / 32;

  this->generate_cipher_key();

  std::ifstream inFile(this->inputFile.c_str(), std::ios::in | std::ifstream::binary);
  std::ofstream encFile(this->encryptedFile.c_str(), std::ios::out | std::ostream::binary);

  while (1)
  {
    std::vector<uint8_t> nBytes = this->get_size_bytes_from_file(inFile);

    if (nBytes.empty())
    {
      break;
    }

    this->perform_encryption(encFile, nBytes);
  }

  inFile.close();
  encFile.close();
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

  std::vector<uint8_t> nBytes(sizeInBytes, '\0');

  inFile.read(reinterpret_cast<char *>(nBytes.data()), sizeInBytes);

  if (inFile.gcount() == 0)
  {
    nBytes.resize(0);
  }

  return nBytes;
}

void AES::perform_encryption(std::ofstream &encFile, std::vector<uint8_t> nBytes)
{
  // for (auto &l : nBytes)
  // {
  //   std::cout << std::hex << l;
  // }
}