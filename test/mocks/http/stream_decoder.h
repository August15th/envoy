#pragma once
#include "envoy/http/codec.h"

#include "gmock/gmock.h"

namespace Envoy {
namespace Http {

class MockStreamDecoder : public virtual StreamDecoder {
public:
  MockStreamDecoder();
  ~MockStreamDecoder() override;

  void decodeMetadata(MetadataMapPtr&& metadata_map) override { decodeMetadata_(metadata_map); }

  // Http::StreamDecoder
  MOCK_METHOD(void, decodeData, (Buffer::Instance & data, bool end_stream));
  MOCK_METHOD(void, decodeMetadata_, (MetadataMapPtr & metadata_map));
};

class MockRequestStreamDecoder : public MockStreamDecoder, public RequestStreamDecoder {
public:
  MockRequestStreamDecoder();
  ~MockRequestStreamDecoder();

  void decodeRequestHeaders(HeaderMapPtr&& headers, bool end_stream) override {
    decodeRequestHeaders_(headers, end_stream);
  }
  void decodeRequestTrailers(HeaderMapPtr&& trailers) override { decodeRequestTrailers_(trailers); }

  // Http::RequestStreamDecoder
  MOCK_METHOD(void, decodeRequestHeaders_, (HeaderMapPtr & headers, bool end_stream));
  MOCK_METHOD(void, decodeRequestTrailers_, (HeaderMapPtr & trailers));
};

class MockResponseStreamDecoder : public MockStreamDecoder, public ResponseStreamDecoder {
public:
  MockResponseStreamDecoder();
  ~MockResponseStreamDecoder();

  void decode100ContinueHeaders(HeaderMapPtr&& headers) override {
    decode100ContinueHeaders_(headers);
  }
  void decodeResponseHeaders(HeaderMapPtr&& headers, bool end_stream) override {
    decodeResponseHeaders_(headers, end_stream);
  }
  void decodeResponseTrailers(HeaderMapPtr&& trailers) override {
    decodeResponseTrailers_(trailers);
  }

  // Http::ResponseStreamDecoder
  MOCK_METHOD(void, decode100ContinueHeaders_, (HeaderMapPtr & headers));
  MOCK_METHOD(void, decodeResponseHeaders_, (HeaderMapPtr & headers, bool end_stream));
  MOCK_METHOD(void, decodeResponseTrailers_, (HeaderMapPtr & trailers));
};

} // namespace Http
} // namespace Envoy
