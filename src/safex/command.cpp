//
// Created by amarko on 4.3.19..
//

#include "cryptonote_config.h"
#include "command.h"
#include "cryptonote_core/cryptonote_tx_utils.h"
#include "cryptonote_basic/cryptonote_format_utils.h"
#include "cryptonote_config.h"
#include "cryptonote_core/blockchain.h"


#undef SAFEX_DEFAULT_LOG_CATEGORY
#define SAFEX_DEFAULT_LOG_CATEGORY "safex"

namespace safex
{

  template<typename CommandResult>
  bool command<CommandResult>::store(epee::serialization::portable_storage &ps) const
  {
    ps.set_value(FIELD_VERSION, (uint32_t) this->version, nullptr);
    ps.set_value(FIELD_COMMAND, (uint32_t) this->command_type, nullptr);

    return true;
  }


  template<typename CommandResult>
  bool command<CommandResult>::load(epee::serialization::portable_storage &ps)
  {


    uint32_t _command_type = 0;

    ps.get_value(FIELD_VERSION, this->version, nullptr);
    ps.get_value(FIELD_COMMAND, _command_type, nullptr);

    this->command_type = static_cast<command_t>(_command_type);

    return true;
  }


  bool token_lock::store(epee::serialization::portable_storage &ps) const
  {
    command<token_lock_result>::store(ps);

    ps.set_value(FIELD_LOCK_TOKEN_AMOUNT, (uint64_t) this->locked_token_amount, nullptr);

    return true;
  }


  bool token_lock::load(epee::serialization::portable_storage &ps)
  {
    command<token_lock_result>::load(ps);

    ps.get_value(FIELD_LOCK_TOKEN_AMOUNT, this->locked_token_amount, nullptr);

    return true;
  }


  bool token_lock::execute(const cryptonote::BlockchainDB &blokchainDB, const cryptonote::txin_to_script &txin, token_lock_result &cr)
  {


    SAFEX_COMMAND_CHECK_AND_ASSERT_THROW_MES((txin.token_amount >= MINIMUM_TOKEN_LOCK_AMOUNT), "Minumum amount of tokens to lock is " + std::to_string(MINIMUM_TOKEN_LOCK_AMOUNT), this->command_type);
    SAFEX_COMMAND_CHECK_AND_ASSERT_THROW_MES((txin.token_amount == this->locked_token_amount), "Amount provided differs from token lock command amount", this->command_type);


    cr.token_amount = txin.token_amount;
    cr.block_number = blokchainDB.height();

    //Calculate hash, locked output ID
    cryptonote::blobdata b_blob = AUTO_VAL_INIT(b_blob);
    b_blob.append(reinterpret_cast<const char *>(&txin.token_amount), sizeof(txin.token_amount));
    b_blob.append(reinterpret_cast<const char *>(&txin.amount), sizeof(txin.amount));
    b_blob.append(reinterpret_cast<const char *>(&(txin.k_image)), sizeof(txin.k_image));
    b_blob.append(reinterpret_cast<const char *>(&cr.block_number), sizeof(cr.block_number));
    cryptonote::get_blob_hash(b_blob, cr.id);

    cr.valid = true;

    return true;
  }


}