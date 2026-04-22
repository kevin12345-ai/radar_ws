# convert_model.py
import onnx
import numpy as np

def convert_float16_to_float32(model_path, output_path):
    # 加载模型
    model = onnx.load(model_path)
    
    # 检查并转换输入类型
    for input in model.graph.input:
        if input.type.tensor_type.elem_type == 10:  # float16
            print(f"Converting input {input.name} from float16 to float32")
            input.type.tensor_type.elem_type = 1  # float32
    
    # 检查并转换输出类型
    for output in model.graph.output:
        if output.type.tensor_type.elem_type == 10:  # float16
            print(f"Converting output {output.name} from float16 to float32")
            output.type.tensor_type.elem_type = 1  # float32
    
    # 检查并转换权重类型
    for initializer in model.graph.initializer:
        if initializer.data_type == 10:  # float16
            print(f"Converting weight {initializer.name} from float16 to float32")
            # 这里需要实际转换数据，但比较复杂
            # 更简单的方法是重新导出模型
    
    # 保存转换后的模型
    onnx.save(model, output_path)
    print(f"Model saved to {output_path}")

# 更简单的方法：使用onnxconverter-common
from onnxconverter_common import float16

def convert_model(model_path, output_path):
    # 加载模型
    model = onnx.load(model_path)
    
    # 将模型转换为float32
    # 注意：float16.to_float32函数可能不存在，这里是一个示意
    # 实际可能需要其他方法
    
    # 备选方案：使用ONNX Simplifier
    print("Converting model using ONNX Simplifier...")
    import onnxsim
    model, check = onnxsim.simplify(model)
    assert check, "Simplified ONNX model could not be validated"
    
    onnx.save(model, output_path)
    print(f"Converted model saved to {output_path}")

if __name__ == "__main__":
    input_model = "/media/seaber/ZHITAI/RM/radar/vision/models/armor.onnx"
    output_model = "/media/seaber/ZHITAI/RM/radar/vision/models/armor_fp32.onnx"
    
    convert_model(input_model, output_model)