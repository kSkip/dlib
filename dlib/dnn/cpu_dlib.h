// Copyright (C) 2015  Davis E. King (davis@dlib.net)
// License: Boost Software License   See LICENSE.txt for the full license.
#ifndef DLIB_DNN_CPU_H_
#define DLIB_DNN_CPU_H_

// This file contains CPU implementations of the GPU based functions in cuda_dlib.h
// and cudnn_dlibapi.h

#include "tensor.h"

namespace dlib
{
    namespace cpu 
    {

    // ----------------------------------------------------------------------------------------

        const double BATCH_NORM_EPS = 0.00001;

    // -----------------------------------------------------------------------------------

        void multiply (
            tensor& dest,
            const tensor& src1,
            const tensor& src2
        );

        void multiply_conv (
            tensor& dest,
            const tensor& src1,
            const tensor& src2
        );

        void add(
            float beta,
            tensor& dest,
            float alpha,
            const tensor& src
        );

        void assign_bias_gradient (
            tensor& grad,
            const tensor& gradient_input
        );

        void add (
            tensor& dest,
            const tensor& src1,
            const tensor& src2
        );

        void assign_conv_bias_gradient (
            tensor& grad,
            const tensor& gradient_input
        );

    // -----------------------------------------------------------------------------------

        void affine_transform(
            tensor& dest,
            const tensor& src,
            const float A,
            const float B
        );

        void affine_transform(
            tensor& dest,
            const tensor& src1,
            const tensor& src2,
            const float A,
            const float B,
            const float C
        );

        void affine_transform(
            tensor& dest,
            const tensor& src1,
            const tensor& src2,
            const tensor& src3,
            const float A,
            const float B,
            const float C,
            const float D
        );

    // -----------------------------------------------------------------------------------

        void affine_transform(
            tensor& dest,
            const tensor& src,
            const tensor& A,
            const tensor& B
        );

    // -----------------------------------------------------------------------------------

        void affine_transform_conv(
            tensor& dest,
            const tensor& src,
            const tensor& A,
            const tensor& B
        );

    // -----------------------------------------------------------------------------------

        void batch_normalize_inference (
            resizable_tensor& dest,
            const tensor& src,
            const tensor& gamma, 
            const tensor& beta,
            const tensor& running_means,
            const tensor& running_invstds
        );

        void batch_normalize (
            resizable_tensor& dest,
            resizable_tensor& means,
            resizable_tensor& invstds,
            const double averaging_factor,
            resizable_tensor& running_means,
            resizable_tensor& running_invstds,
            const tensor& src,
            const tensor& gamma, 
            const tensor& beta 
        );

        void batch_normalize_gradient (
            const tensor& gradient_input,
            const tensor& means,
            const tensor& invstds,
            const tensor& src,
            const tensor& gamma,
            tensor& src_grad,
            tensor& gamma_grad, 
            tensor& beta_grad 
        );

        void batch_normalize_conv_inference (
            resizable_tensor& dest,
            const tensor& src,
            const tensor& gamma, 
            const tensor& beta,
            const tensor& running_means,
            const tensor& running_invstds
        );

        void batch_normalize_conv (
            resizable_tensor& dest,
            resizable_tensor& means,
            resizable_tensor& invstds,
            const double averaging_factor,
            resizable_tensor& running_means,
            resizable_tensor& running_invstds,
            const tensor& src,
            const tensor& gamma, 
            const tensor& beta 
        );

        void batch_normalize_conv_gradient (
            const tensor& gradient_input,
            const tensor& means,
            const tensor& invstds,
            const tensor& src,
            const tensor& gamma,
            tensor& src_grad,
            tensor& gamma_grad, 
            tensor& beta_grad 
        );

    // -----------------------------------------------------------------------------------

        void threshold (
            tensor& data,
            float thresh
        );

        void dot (
            const tensor& a,
            const tensor& b,
            tensor& result,
            size_t idx
        );

    // -----------------------------------------------------------------------------------

        void softmax (
            tensor& dest,
            const tensor& src
        );

        void softmax_gradient (
            tensor& grad,
            const tensor& dest,
            const tensor& gradient_input
        );

    // ------------------------------------------------------------------------------------

        void sigmoid (
            tensor& dest,
            const tensor& src
        );

        void sigmoid_gradient (
            tensor& grad,
            const tensor& dest,
            const tensor& gradient_input
        );

    // ------------------------------------------------------------------------------------

        void relu (
            tensor& dest,
            const tensor& src
        );

        void relu_gradient (
            tensor& grad,
            const tensor& dest,
            const tensor& gradient_input
        );

    // ------------------------------------------------------------------------------------

        void tanh (
            tensor& dest,
            const tensor& src
        );

        void tanh_gradient (
            tensor& grad,
            const tensor& dest,
            const tensor& gradient_input
        );

    // -----------------------------------------------------------------------------------

        class pooling
        {
        public:

            pooling(const pooling&) = delete;
            pooling& operator=(const pooling&) = delete;

            pooling (
            );

            void clear(
            );

            void setup_max_pooling(
                int window_height,
                int window_width,
                int stride_y,
                int stride_x
            );

            void setup_avg_pooling(
                int window_height,
                int window_width,
                int stride_y,
                int stride_x
            );

            bool does_max_pooling(
            ) const { return do_max_pooling; }

            void operator() (
                resizable_tensor& dest,
                const tensor& src
            );

            void get_gradient(
                const tensor& gradient_input, 
                const tensor& dest,
                const tensor& src,
                tensor& grad 
            );

        private:
            int window_height;
            int window_width;
            int stride_y;
            int stride_x;
            bool do_max_pooling;

        };

    // -----------------------------------------------------------------------------------

    } 
}

#ifdef NO_MAKEFILE
#include "cpu_dlib.cpp"
#endif

#endif // DLIB_DNN_CPU_H_

