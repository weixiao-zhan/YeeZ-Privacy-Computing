#pragma once
#include "hpda/processor/processor.h"
#include "stbox/ebyte.h"
#include "stbox/eth/eth_hash.h"
#include "stbox/stx_common.h"
#include "stbox/tsgx/channel/dh_session_initiator.h"
#include "stbox/tsgx/log.h"
#include "ypc_t/ecommon/package.h"
#include <ff/util/ntobject.h>

namespace ypc{

using bytes = ::stbox::bytes;
typedef ::ff::util::ntobject<nt<bytes>::data> extra_data_source_output_t;
typedef ::ff::util::ntobject<nt<bytes>::data> extra_data_source_output_t;
template<typename NTObj>
  class to_type : ::hpda::processor::internal::processor_base<extra_data_source_output_t, NTObj>{
    public:
      processor_base(::hpda::internal::processor_with_output<extra_data_source_output_t> * upper_stream)
        : hpda::processor::internal::processor_base<extra_data_source_output_t, NTObj>(upper_stream){}

      typedef processor_base<extra_data_source_output_t, NTObj> base;
      virtual bool process(){
        if (!base::has_input_value()) {
          return false;
        }

        using ntt = nt<stbox::bytes>;
        const stbox::bytes &data = base::input_value().get<ntt::data>();
        m_data = ntpackage_item_parser<stbox::bytes, NTObj>::parser(
            data.data(), data.size());
        return true;
      }

      virtual NTObj output_value() { return m_data; }

    protected:
      NTObj m_data;
  };

}
