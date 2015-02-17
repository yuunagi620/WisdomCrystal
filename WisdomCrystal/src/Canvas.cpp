// Canvas.cpp

#include "Canvas.h"


Canvas::Canvas() : mRenderTarget(nullptr)
{

}


Canvas::~Canvas() {
    // empty
}


void Canvas::Init(GraphicsDevice* graphicsDevice) {
    mRenderTarget = graphicsDevice->GetRenderTarget();
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
