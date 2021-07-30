#include "aes.h"
#include <iostream>
#include <iomanip>

AES::AES(int size, std::string inputFile, std::string encryptedFile, std::string decryptedFile)
{
  this->size = size;
  this->inputFile = inputFile;
  this->encryptedFile = encryptedFile;
  this->decryptedFile = decryptedFile;
  this->columns = this->size / 32;

  switch (this->size)
  {
  case 128:
    this->numberRounds = 10;
    break;
  case 192:
    this->numberRounds = 12;
    break;
  case 265:
    this->numberRounds = 14;
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

void AES::write_size_bytes_to_file(std::ofstream &encFile, std::vector<std::vector<uint8_t>> output)
{
  for (int j = 0; j < this->columns; j++)
  {
    for (int i = 0; i < this->rows; i++)
    {
      encFile << "0x" << std::hex << std::setw(2) << std::setfill('0') << int(output[i][j]) << " ";
    }
  }
}

void AES::perform_encryption(std::ofstream &encFile, std::vector<uint8_t> nBytes)
{
  std::vector<std::vector<uint8_t>> state;
  state.resize(this->rows, std::vector<uint8_t>(this->columns, '\0'));

  for (int j = 0; j < this->columns; j++)
  {
    for (int i = 0; i < this->rows; i++)
    {
      state[i][j] = nBytes[j * this->rows + i];
    }
  }

  this->add_round_key(state);

  for (int i = 0; i < this->numberRounds; i++)
  {
    this->sub_bytes(state);
    this->shift_rows(state);
    this->mix_columns(state);
    this->add_round_key(state);
  }

  this->sub_bytes(state);
  this->shift_rows(state);
  this->add_round_key(state);

  this->write_size_bytes_to_file(encFile, state);
}

void AES::add_round_key(std::vector<std::vector<uint8_t>> &state)
{
  for (int j = 0; j < this->columns; j++)
  {
    for (int i = 0; i < this->rows; i++)
    {
      state[i][j] ^= this->cipherKey[j * this->rows + i];
    }
  }
}
void AES::sub_bytes(std::vector<std::vector<uint8_t>> &state)
{
  for (int i = 0; i < this->rows; i++)
  {
    for (int j = 0; j < this->columns; j++)
    {
      int row = state[i][j] & 0xf0;
      int column = state[i][j] & 0xf;

      state[i][j] = this->multiplicativeInverse[row][column];
    }
  }
}
void AES::shift_rows(std::vector<std::vector<uint8_t>> &state)
{
  for (int i = 0; i < this->rows; i++)
  {
    std::vector<uint8_t> shifted(this->columns);
    for (int j = 0; j < this->columns; j++)
    {
      shifted[j] = state[i][(i + j) % this->columns];
    }
    for (int j = 0; j < this->columns; j++)
    {
      state[i][j] = shifted[j];
    }
  }
}
void AES::mix_columns(std::vector<std::vector<uint8_t>> &state)
{
  for (int j = 0; j < this->columns; j++)
  {

    std::vector<uint8_t> mixed(4);

    mixed.push_back((gf_mul(state[0][j], 0x2) ^ gf_mul(state[1][j], 0x3) ^ state[2][j] ^ state[3][j]));
    mixed.push_back((state[0][j] ^ gf_mul(state[1][j], 0x2) ^ gf_mul(state[2][j], 0x3) ^ state[3][j]));
    mixed.push_back((state[0][j] ^ state[1][j] ^ gf_mul(state[2][j], 0x2) ^ gf_mul(state[3][j], 0x3)));
    mixed.push_back((gf_mul(state[0][j], 0x3) ^ state[1][j] ^ state[2][j] ^ gf_mul(state[3][j], 0x2)));

    state[0][j] = mixed[0];
    state[1][j] = mixed[1];
    state[2][j] = mixed[2];
    state[3][j] = mixed[3];
  }
}

uint8_t AES::gf_mul(uint8_t a, uint8_t b)
{
  uint8_t p = 0;
  uint8_t high_bit_mask = 0x80;
  uint8_t high_bit = 0;
  uint8_t modulo = 0x1B; /* x^8 + x^4 + x^3 + x + 1 */

  for (int i = 0; i < 8; i++)
  {
    if (b & 1)
    {
      p ^= a;
    }

    high_bit = a & high_bit_mask;
    a <<= 1;
    if (high_bit)
    {
      a ^= modulo;
    }
    b >>= 1;
  }

  return p;
}

void AES::print_state(std::vector<std::vector<uint8_t>> state)
{

  for (int i = 0; i < this->rows; i++)
  {
    for (int j = 0; j < this->columns; j++)
    {
      std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << int(state[i][j]) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}