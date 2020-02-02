#pragma once

#include "envoy/http/codec.h"

#include "test/mocks/http/stream.h"

#include "gmock/gmock.h"

namespace Envoy {
namespace Http {

class MockStreamEncoder : public virtual StreamEncoder {
public:
  MockStreamEncoder();
  ~MockStreamEncoder() override;

  // Http::StreamEncoder
  MOCK_METHOD(void, encodeData, (Buffer::Instance & data, bool end_stream));
  MOCK_METHOD(void, encodeMetadata, (const MetadataMapVector& metadata_map_vector));
  MOCK_METHOD(Stream&, getStream, ());

  testing::NiceMock<MockStream> stream_;
};

class MockRequestStreamEncoder : public MockStreamEncoder, public RequestStreamEncoder {
public:
  MockRequestStreamEncoder();
  ~MockRequestStreamEncoder();

  // Http::RequestStreamEncoder
  MOCK_METHOD(void, encodeRequestHeaders, (const HeaderMap& headers, bool end_stream));
  MOCK_METHOD(void, encodeRequestTrailers, (const HeaderMap& trailers));
};

class MockResponseStreamEncoder : public MockStreamEncoder, public ResponseStreamEncoder {
public:
  MockResponseStreamEncoder();
  ~MockResponseStreamEncoder();

  // Http::ResponseStreamEncoder
  MOCK_METHOD(void, encode100ContinueHeaders, (const HeaderMap& headers));
  MOCK_METHOD(void, encodeResponseHeaders, (const HeaderMap& headers, bool end_stream));
  MOCK_METHOD(void, encodeResponseTrailers, (const HeaderMap& trailers));
};

} // namespace Http
} // namespace Envoy
