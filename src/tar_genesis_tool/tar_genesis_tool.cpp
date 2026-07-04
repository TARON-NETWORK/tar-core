// Generates the GENESIS_TX hex blob for the TAR genesis premine.
// Usage: tar_genesis_tool <dev-fund-tar-address>
#include <cstdint>
#include <iostream>

#include "string_tools.h"
#include "crypto/crypto.h"
#include "device/device.hpp"
#include "cryptonote_config.h"
#include "cryptonote_basic/cryptonote_basic.h"
#include "cryptonote_basic/cryptonote_basic_impl.h"
#include "cryptonote_basic/cryptonote_format_utils.h"

using namespace cryptonote;

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "usage: " << argv[0] << " <tar-dev-fund-address>" << std::endl;
    return 1;
  }

  address_parse_info info;
  if (!get_account_address_from_str(info, MAINNET, argv[1]))
  {
    std::cerr << "invalid TAR address: " << argv[1] << std::endl;
    return 1;
  }

  static const uint64_t PREMINE_ATOMIC = 50000000ULL * COIN; // 5% of 1,000,000,000 TAR

  transaction tx{};
  keypair txkey = keypair::generate(hw::get_device("default"));
  add_tx_pub_key_to_extra(tx, txkey.pub);

  txin_gen in{};
  in.height = 0;
  tx.vin.push_back(in);

  crypto::key_derivation derivation;
  if (!crypto::generate_key_derivation(info.address.m_view_public_key, txkey.sec, derivation))
  {
    std::cerr << "generate_key_derivation failed" << std::endl;
    return 1;
  }

  crypto::public_key out_eph_public_key;
  if (!crypto::derive_public_key(derivation, 0, info.address.m_spend_public_key, out_eph_public_key))
  {
    std::cerr << "derive_public_key failed" << std::endl;
    return 1;
  }

  tx_out out{};
  crypto::view_tag view_tag{};
  cryptonote::set_tx_out(PREMINE_ATOMIC, out_eph_public_key, false, view_tag, out);
  tx.vout.push_back(out);

  tx.version = 1;
  tx.unlock_time = CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW; // height 0 + 60 blocks, same rule as any miner tx
  tx.invalidate_hashes();

  blobdata blob = tx_to_blob(tx);
  std::cout << epee::string_tools::buff_to_hex_nodelimer(blob) << std::endl;
  return 0;
}
