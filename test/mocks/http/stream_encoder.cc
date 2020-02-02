#include "test/mocks/http/stream_encoder.h"

namespace Envoy {
namespace Http {

MockStreamEncoder::MockStreamEncoder() {
  ON_CALL(*this, getStream()).WillByDefault(ReturnRef(stream_));
}

MockStreamEncoder::~MockStreamEncoder() = default;

MockRequestStreamEncoder::MockRequestStreamEncoder() = default;
MockRequestStreamEncoder::~MockRequestStreamEncoder() = default;

MockResponseStreamEncoder::MockResponseStreamEncoder() = default;
MockResponseStreamEncoder::~MockResponseStreamEncoder() = default;

} // namespace Http
} // namespace Envoy
