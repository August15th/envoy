#include "common/http/codec_wrappers.h"

#include "test/mocks/http/mocks.h"
#include "test/test_common/utility.h"

using testing::_;

namespace Envoy {
namespace Http {

class MockRequestStreamEncoderWrapper : public RequestStreamEncoderWrapper {
public:
  MockRequestStreamEncoderWrapper() : RequestStreamEncoderWrapper(inner_encoder_) {}
  void onEncodeComplete() override { encode_complete_ = true; }

  MockRequestStreamEncoder& innerEncoder() { return inner_encoder_; }
  bool encodeComplete() const { return encode_complete_; }

private:
  MockRequestStreamEncoder inner_encoder_;
  bool encode_complete_{};
};

TEST(RequestStreamEncoderWrapper, HeaderOnlyEncode) {
  MockRequestStreamEncoderWrapper wrapper;

  EXPECT_CALL(wrapper.innerEncoder(), encodeRequestHeaders(_, true));
  wrapper.encodeRequestHeaders(TestHeaderMapImpl{{":status", "200"}}, true);
  EXPECT_TRUE(wrapper.encodeComplete());
}

TEST(RequestStreamEncoderWrapper, HeaderAndBodyEncode) {
  MockRequestStreamEncoderWrapper wrapper;

  TestHeaderMapImpl response_headers{{":status", "200"}};
  EXPECT_CALL(wrapper.innerEncoder(), encodeRequestHeaders(_, false));
  wrapper.encodeRequestHeaders(response_headers, false);
  EXPECT_FALSE(wrapper.encodeComplete());

  Buffer::OwnedImpl data;
  EXPECT_CALL(wrapper.innerEncoder(), encodeData(_, true));
  wrapper.encodeData(data, true);
  EXPECT_TRUE(wrapper.encodeComplete());
}

TEST(RequestStreamEncoderWrapper, HeaderAndBodyAndTrailersEncode) {
  MockRequestStreamEncoderWrapper wrapper;

  TestHeaderMapImpl response_headers{{":status", "200"}};
  EXPECT_CALL(wrapper.innerEncoder(), encodeRequestHeaders(_, false));
  wrapper.encodeRequestHeaders(response_headers, false);
  EXPECT_FALSE(wrapper.encodeComplete());

  Buffer::OwnedImpl data;
  EXPECT_CALL(wrapper.innerEncoder(), encodeData(_, false));
  wrapper.encodeData(data, false);
  EXPECT_FALSE(wrapper.encodeComplete());

  EXPECT_CALL(wrapper.innerEncoder(), encodeRequestTrailers(_));
  wrapper.encodeRequestTrailers(TestHeaderMapImpl{{"trailing", "header"}});
  EXPECT_TRUE(wrapper.encodeComplete());
}

} // namespace Http
} // namespace Envoy
