import numpy as np
import cv2
import os


def calc_energy_map(image):
    b, g, r = cv2.split(image)
    b_energy = np.absolute(cv2.Scharr(b, -1, 1, 0)) + \
        np.absolute(cv2.Scharr(b, -1, 0, 1))
    g_energy = np.absolute(cv2.Scharr(g, -1, 1, 0)) + \
        np.absolute(cv2.Scharr(g, -1, 0, 1))
    r_energy = np.absolute(cv2.Scharr(r, -1, 1, 0)) + \
        np.absolute(cv2.Scharr(r, -1, 0, 1))
    return b_energy + g_energy + r_energy


def seam_carving(input_path, output_path):
    # 读取图片
    image = cv2.imread(input_path)
    out_image = np.copy(image)
    target_width = image.shape[1] // 2

    ##############################

    while out_image.shape[1] > target_width:

        count += 1

        # 计算能量图
        energy_map = calc_energy_map(out_image)

        # 定义动态规划数组
        # dp_map[i][j]表示从第i行第j列到最后一行的最小能量和
        # dp_path[i][j]表示从第i行第j列的上一像素点的列数
        r, c = out_image.shape[0], out_image.shape[1]
        dp_map = np.zeros((r, c))
        dp_map[0] = energy_map[0]
        dp_path = np.zeros((r, c))

        # 填表
        for i in range(1, r):
            for j in range(0, c):
                # 最小能量相邻像素的列坐标
                min_energy_col = j - 1 + np.argmin([dp_map[i-1][j-1] if j-1 >= 0 else float('inf'),
                                                    dp_map[i-1][j],
                                                    dp_map[i-1][j+1] if j+1 < c else float('inf')])

                # 更新dp_map
                dp_map[i][j] = energy_map[i][j] + dp_map[i-1][min_energy_col]

                # 更新dp_path
                dp_path[i][j] = min_energy_col

        # 回溯dp_path找到最小能量路径
        seam = []
        for i in range(r-1, -1, -1):
            col = int(dp_path[i][col]) if i != r - \
                1 else np.argmin(dp_map[r-1])
            seam.append(col)

        # 沿着seam删除像素
        output = np.zeros((r, c - 1, 3))
        for i in range(r - 1, -1, -1):
            col = seam[i]
            output[i, :, 0] = np.delete(out_image[i, :, 0], [col])
            output[i, :, 1] = np.delete(out_image[i, :, 1], [col])
            output[i, :, 2] = np.delete(out_image[i, :, 2], [col])
        out_image = np.copy(output)

    ##############################

    # 保存图片
    cv2.imwrite(output_path, out_image.astype(np.uint8))


def main():
    input_path = os.path.join(os.path.dirname(__file__), 'input.jpg')
    output_path = os.path.join(os.path.dirname(__file__), 'output.jpg')

    seam_carving(input_path, output_path)


if __name__ == '__main__':
    main()
