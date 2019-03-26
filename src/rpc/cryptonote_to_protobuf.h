// Copyright (c) 2019, The Safex Project
// 
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
//    of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be
//    used to endorse or promote products derived from this software without specific
//    prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Parts of this file are originally copyright (c) 2017-2018 The Monero Project


// Wrappers around protobuf classes. Logic for converting cryptonote objects to protobuf object representation.

#ifndef SAFEX_CRYPTONOTE_TO_PROTOBUF_H
#define SAFEX_CRYPTONOTE_TO_PROTOBUF_H

#include "transactions.pb.h"
#include "blocks.pb.h"
#include "../cryptonote_basic/cryptonote_basic.h"
#include "../cryptonote_core/cryptonote_core.h"
#include <google/protobuf/text_format.h>
#include <string>

namespace safex {

    // Base class for protobuf endpoint.
    // @todo Add stream support.
    class protobuf_endpoint {
    public:
        virtual std::string string() const = 0;
    };

    // @brief Utility class for encapsulating cryptonot::transaction to protobuf serialization.
    //        Encapsulates whole get transaction response.
    // @see proto/transactions.proto 
    class transactions_protobuf : public protobuf_endpoint {
    public:
        transactions_protobuf();
        ~transactions_protobuf();

        // @brief Adding cryptonote::transaction to protobuf strucutre for serialization.
        // @param cryptnote::transaction Input transaction to be 
        // @return pointer to protobuf transaction structure.
        safex::Transaction* add_transaction(const cryptonote::transaction &tx);

        // @brief Getting last added transaction to response.
        // @return pointer to last added transaction (protobuf structure)
        safex::Transaction *last();

        // @brief Static method for extracting data from cryponote::transaction and putting in protobuf structure.
        // @param pointer to protobuf transaction structure
        // @param reference of cryptnote::transaction
        static void fill_proto_tx(safex::Transaction* prototx, const cryptonote::transaction& tx);

        // @brief Adding missed tx hash.
        // @params string Missed tx hash.
        void add_missed_tx(const std::string& missed);

        // @brief Get string representation of protobuf serialization.
        // @return string serialized data
        std::string string() const;

    private:
        safex::Transactions m_txs; //< Contains whole response data.
        safex::Transaction *m_last; //< Contains just last transaction added.
    };

    // @brief Utility class for encapsulating cryptonote::block to protobuf structure for further
    //        platform independent binary serialization.
    // @see proto/blocks.proto 
    class blocks_protobuf : public protobuf_endpoint {
    public:
        blocks_protobuf();
        ~blocks_protobuf();

<<<<<<< HEAD
        // @brief Getting all necessary data for block and serializing.
        // @param reference to cryptonote::block
        // @param list of transactions in given block
        void add_block(const cryptonote::block& blck, const std::list<cryptonote::transaction>& txs);
=======
        void add_block(const cryptonote::block& blck);
>>>>>>> Small changes on protobuf related stuff
        void add_error(const std::string& err);

        // @brief Get string representation of protobuf serialization.
        // @return string serialized data
        std::string string() const;
    private:
        safex::Blocks m_blcks;

        // @brief Getting protobuf BlockHeader structur from cryptonote::block
        // @0param reference to cryptnote::block
        safex::BlockHeader* proto_block_header(const cryptonote::block& blck);

    };

}

#endif //SAFEX_CRYPTONOTE_TO_PROTOBUF_H