/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "ABI49_0_0TransactionTelemetry.h"

#include <ABI49_0_0React/debug/ABI49_0_0React_native_assert.h>

#include <utility>

namespace ABI49_0_0facebook::ABI49_0_0React {

thread_local TransactionTelemetry *threadLocalTransactionTelemetry = nullptr;

TransactionTelemetry::TransactionTelemetry()
    : TransactionTelemetry(telemetryTimePointNow) {}

TransactionTelemetry::TransactionTelemetry(
    std::function<TelemetryTimePoint()> now)
    : now_{std::move(now)} {}

TransactionTelemetry *TransactionTelemetry::threadLocalTelemetry() {
  return threadLocalTransactionTelemetry;
}

void TransactionTelemetry::setAsThreadLocal() {
  threadLocalTransactionTelemetry = this;
}

void TransactionTelemetry::unsetAsThreadLocal() {
  threadLocalTransactionTelemetry = nullptr;
}

void TransactionTelemetry::willCommit() {
  ABI49_0_0React_native_assert(commitStartTime_ == kTelemetryUndefinedTimePoint);
  ABI49_0_0React_native_assert(commitEndTime_ == kTelemetryUndefinedTimePoint);
  commitStartTime_ = now_();
}

void TransactionTelemetry::didCommit() {
  ABI49_0_0React_native_assert(commitStartTime_ != kTelemetryUndefinedTimePoint);
  ABI49_0_0React_native_assert(commitEndTime_ == kTelemetryUndefinedTimePoint);
  commitEndTime_ = now_();
}

void TransactionTelemetry::willDiff() {
  ABI49_0_0React_native_assert(diffStartTime_ == kTelemetryUndefinedTimePoint);
  ABI49_0_0React_native_assert(diffEndTime_ == kTelemetryUndefinedTimePoint);
  diffStartTime_ = now_();
}

void TransactionTelemetry::didDiff() {
  ABI49_0_0React_native_assert(diffStartTime_ != kTelemetryUndefinedTimePoint);
  ABI49_0_0React_native_assert(diffEndTime_ == kTelemetryUndefinedTimePoint);
  diffEndTime_ = now_();
}

void TransactionTelemetry::willLayout() {
  ABI49_0_0React_native_assert(layoutStartTime_ == kTelemetryUndefinedTimePoint);
  ABI49_0_0React_native_assert(layoutEndTime_ == kTelemetryUndefinedTimePoint);
  layoutStartTime_ = now_();
}

void TransactionTelemetry::willMeasureText() {
  ABI49_0_0React_native_assert(
      lastTextMeasureStartTime_ == kTelemetryUndefinedTimePoint);
  lastTextMeasureStartTime_ = now_();
}

void TransactionTelemetry::didMeasureText() {
  numberOfTextMeasurements_++;
  ABI49_0_0React_native_assert(
      lastTextMeasureStartTime_ != kTelemetryUndefinedTimePoint);
  textMeasureTime_ += now_() - lastTextMeasureStartTime_;
  lastTextMeasureStartTime_ = kTelemetryUndefinedTimePoint;
}

void TransactionTelemetry::didLayout() {
  ABI49_0_0React_native_assert(layoutStartTime_ != kTelemetryUndefinedTimePoint);
  ABI49_0_0React_native_assert(layoutEndTime_ == kTelemetryUndefinedTimePoint);
  layoutEndTime_ = now_();
}

void TransactionTelemetry::willMount() {
  ABI49_0_0React_native_assert(mountStartTime_ == kTelemetryUndefinedTimePoint);
  ABI49_0_0React_native_assert(mountEndTime_ == kTelemetryUndefinedTimePoint);
  mountStartTime_ = now_();
}

void TransactionTelemetry::didMount() {
  ABI49_0_0React_native_assert(mountStartTime_ != kTelemetryUndefinedTimePoint);
  ABI49_0_0React_native_assert(mountEndTime_ == kTelemetryUndefinedTimePoint);
  mountEndTime_ = now_();
}

void TransactionTelemetry::setRevisionNumber(int revisionNumber) {
  revisionNumber_ = revisionNumber;
}

TelemetryTimePoint TransactionTelemetry::getDiffStartTime() const {
  ABI49_0_0React_native_assert(diffStartTime_ != kTelemetryUndefinedTimePoint);
  ABI49_0_0React_native_assert(diffEndTime_ != kTelemetryUndefinedTimePoint);
  return diffStartTime_;
}

TelemetryTimePoint TransactionTelemetry::getDiffEndTime() const {
  ABI49_0_0React_native_assert(diffStartTime_ != kTelemetryUndefinedTimePoint);
  ABI49_0_0React_native_assert(diffEndTime_ != kTelemetryUndefinedTimePoint);
  return diffEndTime_;
}

TelemetryTimePoint TransactionTelemetry::getCommitStartTime() const {
  ABI49_0_0React_native_assert(commitStartTime_ != kTelemetryUndefinedTimePoint);
  ABI49_0_0React_native_assert(commitEndTime_ != kTelemetryUndefinedTimePoint);
  return commitStartTime_;
}

TelemetryTimePoint TransactionTelemetry::getCommitEndTime() const {
  ABI49_0_0React_native_assert(commitStartTime_ != kTelemetryUndefinedTimePoint);
  ABI49_0_0React_native_assert(commitEndTime_ != kTelemetryUndefinedTimePoint);
  return commitEndTime_;
}

TelemetryTimePoint TransactionTelemetry::getLayoutStartTime() const {
  ABI49_0_0React_native_assert(layoutStartTime_ != kTelemetryUndefinedTimePoint);
  ABI49_0_0React_native_assert(layoutEndTime_ != kTelemetryUndefinedTimePoint);
  return layoutStartTime_;
}

TelemetryTimePoint TransactionTelemetry::getLayoutEndTime() const {
  ABI49_0_0React_native_assert(layoutStartTime_ != kTelemetryUndefinedTimePoint);
  ABI49_0_0React_native_assert(layoutEndTime_ != kTelemetryUndefinedTimePoint);
  return layoutEndTime_;
}

TelemetryTimePoint TransactionTelemetry::getMountStartTime() const {
  ABI49_0_0React_native_assert(mountStartTime_ != kTelemetryUndefinedTimePoint);
  ABI49_0_0React_native_assert(mountEndTime_ != kTelemetryUndefinedTimePoint);
  return mountStartTime_;
}

TelemetryTimePoint TransactionTelemetry::getMountEndTime() const {
  ABI49_0_0React_native_assert(mountStartTime_ != kTelemetryUndefinedTimePoint);
  ABI49_0_0React_native_assert(mountEndTime_ != kTelemetryUndefinedTimePoint);
  return mountEndTime_;
}

TelemetryDuration TransactionTelemetry::getTextMeasureTime() const {
  return textMeasureTime_;
}

int TransactionTelemetry::getNumberOfTextMeasurements() const {
  return numberOfTextMeasurements_;
}

int TransactionTelemetry::getRevisionNumber() const {
  return revisionNumber_;
}

} // namespace ABI49_0_0facebook::ABI49_0_0React
