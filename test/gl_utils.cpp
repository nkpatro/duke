#include "duke/gl/GL.hpp"
#include "duke/gl/GlUtils.hpp"

#include <gtest/gtest.h>

void checkBackAndForth(int32_t glFormat) {
  const auto channels = getChannels(glFormat);
  const auto actual = getOpenGlFormat(channels);
  EXPECT_EQ(glFormat, actual) << "source   : " << getInternalFormatString(glFormat) << '\n'
                              << "channels : " << channels.asString() << '\n'
                              << "actual   : " << getInternalFormatString(actual);
}

TEST(GlUtils, ChannelsToGl) {
  checkBackAndForth(GL_R16);
  checkBackAndForth(GL_R16F);
  checkBackAndForth(GL_R16I);
  checkBackAndForth(GL_R16_SNORM);
  checkBackAndForth(GL_R16UI);
  checkBackAndForth(GL_R32F);
  checkBackAndForth(GL_R32I);
  checkBackAndForth(GL_R32UI);
  checkBackAndForth(GL_R3_G3_B2);
  checkBackAndForth(GL_R8);
  checkBackAndForth(GL_R8I);
  checkBackAndForth(GL_R8_SNORM);
  checkBackAndForth(GL_R8UI);
  checkBackAndForth(GL_RG16);
  checkBackAndForth(GL_RG16F);
  checkBackAndForth(GL_RG16I);
  checkBackAndForth(GL_RG16_SNORM);
  checkBackAndForth(GL_RG16UI);
  checkBackAndForth(GL_RG32F);
  checkBackAndForth(GL_RG32I);
  checkBackAndForth(GL_RG32UI);
  checkBackAndForth(GL_RG8);
  checkBackAndForth(GL_RG8I);
  checkBackAndForth(GL_RG8_SNORM);
  checkBackAndForth(GL_RG8UI);
  checkBackAndForth(GL_RGB10);
  checkBackAndForth(GL_RGB10_A2);
  checkBackAndForth(GL_RGB10_A2UI);
  checkBackAndForth(GL_RGB12);
  checkBackAndForth(GL_RGB16);
  checkBackAndForth(GL_RGB16F);
  checkBackAndForth(GL_RGB16I);
  checkBackAndForth(GL_RGB16_SNORM);
  checkBackAndForth(GL_RGB16UI);
  checkBackAndForth(GL_RGB32F);
  checkBackAndForth(GL_RGB32I);
  checkBackAndForth(GL_RGB32UI);
  checkBackAndForth(GL_RGB4);
  checkBackAndForth(GL_RGB5);
  checkBackAndForth(GL_RGB5_A1);
  checkBackAndForth(GL_RGB8);
  checkBackAndForth(GL_RGB8I);
  checkBackAndForth(GL_RGB8_SNORM);
  checkBackAndForth(GL_RGB8UI);
  checkBackAndForth(GL_RGBA12);
  checkBackAndForth(GL_RGBA16);
  checkBackAndForth(GL_RGBA16F);
  checkBackAndForth(GL_RGBA16I);
  checkBackAndForth(GL_RGBA16_SNORM);
  checkBackAndForth(GL_RGBA16UI);
  checkBackAndForth(GL_RGBA2);
  checkBackAndForth(GL_RGBA32F);
  checkBackAndForth(GL_RGBA32I);
  checkBackAndForth(GL_RGBA32UI);
  checkBackAndForth(GL_RGBA4);
  checkBackAndForth(GL_RGBA8);
  checkBackAndForth(GL_RGBA8I);
  checkBackAndForth(GL_RGBA8_SNORM);
  checkBackAndForth(GL_RGBA8UI);
}
