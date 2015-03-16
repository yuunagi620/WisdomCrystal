// Canvas.cpp

#include "Canvas.h"


Canvas::Canvas()
    : mRenderTarget(nullptr) {
    // empty
}


Canvas::~Canvas() {
    // empty
}


void Canvas::Init(GraphicsDevice* graphicsDevice) {
    mRenderTarget = graphicsDevice->GetRenderTarget();
}


void Canvas::Clear(D2D1_COLOR_F& fillColor) {
    mRenderTarget->Clear(fillColor);
}


void Canvas::ResetTransform() {
    mRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}


void Canvas::FlipHorizontal(float centerX, float centerY) {
    mRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(-1, 1, D2D1::Point2F(centerX, centerY)));
}


void Canvas::FlipVertical(float centerX, float centerY) {
    mRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(1, -1, D2D1::Point2F(centerX, centerY)));
}


void Canvas::RotateTransform(float centerX, float centerY, float angle) {
    mRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(centerX, centerY)));
}


void Canvas::FillRectangle(int x, int y, int width, int height, const D2DBrush& brush) {
    mRenderTarget->FillRectangle(D2D1::RectF(static_cast<float>(x),
                                             static_cast<float>(y),
                                             static_cast<float>(width),
                                             static_cast<float>(height)),
                                 brush.GetBrush());
}

void Canvas::FillRectangle(float x, float y, float width, float height, const D2DBrush& brush) {
    mRenderTarget->FillRectangle(D2D1::RectF(x, y, width, height), brush.GetBrush());
}