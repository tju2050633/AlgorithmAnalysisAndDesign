from math import exp

# 定义目标函数
def f(x1, x2):
    return exp(x1 + 3 * x2 - 0.1) + exp(x1 - 3 * x2 - 0.1) + exp(-x1 - 0.1)

# 定义目标函数关于自变量的偏导数
def df_dx1(x1, x2):
    return exp(x1 + 3 * x2 - 0.1) + exp(x1 - 3 * x2 - 0.1) - exp(-x1 - 0.1)


def df_dx2(x1, x2):
    return 3 * exp(x1 + 3 * x2 - 0.1) - 3 * exp(x1 - 3 * x2 - 0.1)


# 设置初始点
x1, x2 = 0, 0

# 设置超参数
lr = 0.0002
n = 100000
treshhold = 1e-10

# 迭代更新自变量
for i in range(n):
    # 计算梯度
    gradient_x1 = df_dx1(x1, x2)
    gradient_x2 = df_dx2(x1, x2)

    # 计算自变量的变化量
    d_x1 = lr * gradient_x1
    d_x2 = lr * gradient_x2

    # 与阈值比较，小于阈值则退出迭代
    if abs(d_x1) < treshhold and abs(d_x2) < treshhold:
        break

    # 更新自变量
    x1 -= d_x1
    x2 -= d_x2

# 输出最小值和对应自变量取值
print(f"x1*= {x1:.10f} x2*= {x2:.10f}".format(x1, x2))
f = f(x1, x2)
print(f"f*= {f:.10f}".format(f))
