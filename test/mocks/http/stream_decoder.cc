#include "test/mocks/http/stream_decoder.h"

namespace Envoy {
namespace Http {

MockStreamDecoder::MockStreamDecoder() = default;
MockStreamDecoder::~MockStreamDecoder() = default;

MockRequestStreamDecoder::MockRequestStreamDecoder() = default;
MockRequestStreamDecoder::~MockRequestStreamDecoder() = default;

MockResponseStreamDecoder::MockResponseStreamDecoder() = default;
MockResponseStreamDecoder::~MockResponseStreamDecoder() = default;

} // namespace Http
} // namespace Envoy
