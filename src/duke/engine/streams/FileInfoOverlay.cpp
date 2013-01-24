/*
 * FileInfoOverlay.cpp
 *
 *  Created on: Jan 9, 2013
 *      Author: Guillaume Chatelet
 */

#include "FileInfoOverlay.h"

#include <duke/engine/rendering/GlyphRenderer.h>
#include <duke/engine/streams/SingleFrameStream.h>
#include <duke/engine/Context.h>

#include <sstream>
#include <iostream>
using namespace std;

namespace duke {
FileInfoOverlay::FileInfoOverlay(const std::shared_ptr<GlyphRenderer>& pRenderer, const std::shared_ptr<SingleFrameStream>& pFileStream) :
                m_pRenderer(pRenderer), m_pFileStream(pFileStream) {
}

void FileInfoOverlay::doRender(const Context& context) const {
    if (!m_pFileStream)
        return;
    std::ostringstream oss;
    oss << m_pFileStream->getAttributes();
    drawText(*m_pRenderer, context.viewport, oss.str().c_str(), 100, 100, 1, 2);
}

} /* namespace duke */
