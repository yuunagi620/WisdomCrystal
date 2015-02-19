// Canvas.cpp

#include "Canvas.h"


Canvas::Canvas() : mRenderTarget(nullptr) {
    // empty
}


Canvas::~Canvas() {
    // empty
}


void Canvas::Init(GraphicsDevice* graphicsDevice) {
    mRenderTarget = graphicsDevice->GetRenderTarget();
}


void Canvas::Clear(const D2D1_COLOR_F& fillColor) {
    mRenderTarget->Clear(fillColor);
}


void Canvas::ResetTransform() {
    mRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}


void Canvas::FlipHorizontal(const float centerX, const float centerY) {
    mRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(-1, 1, D2D1::Point2F(centerX, centerY)));
}


void Canvas::FlipVertical(const float centerX, const float centerY) {
    mRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(1, -1, D2D1::Point2F(centerX, centerY)));
}


void Canvas::RotateTransform(const float centerX, const float centerY, const float angle) {
    mRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(centerX, centerY)));
}


void Canvas::FillRectangle(const int x, const int y, const int width, const int height, const D2DBrush& brush) {
    mRenderTarget->FillRectangle(D2D1::RectF(static_cast<float>(x),
                                             static_cast<float>(y),
                                             static_cast<float>(width),
                                             static_cast<float>(height)),
                                 brush.GetBrush());
}

void Canvas::FillRectangle(const float x,
                           const float y,
                           const float width,
                           const float height,
                           const D2DBrush& brush) {
    mRenderTarget->FillRectangle(D2D1::RectF(x, y, width, height), brush.GetBrush());
}