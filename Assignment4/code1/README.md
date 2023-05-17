# seam carving算法实现



### 运行

1. 安装python3和PyPi

2. 安装依赖项`cv2`和`numpy`

   ```shell
   pip3 install opencv-python numpy
   ```

3. 将python代码与输入图像（命名为`input.jpg`）放在同一目录下

4. 运行命令：

   ```shell
   python3 seam_carving.py
   ```

   

   输出结果图像路径：`./output.jpg`



### 复杂度分析

主要函数代码：

<img src=code2.png alt="Image" width="70%">

<img src=code1.png alt="Image" width="70%">



设图像宽度$W$，高度$H$。

- 时间复杂度

循环次数为$W / 2$，每次循环执行操作包括：计算能量图，填$dp\_map$和$dp\_path$表，回溯找最小能量路径，沿着seam删除像素。

计算能量图需要遍历3个通道上的每个像素点，共$3\times W\times H \times 2$次梯度计算，时间复杂度$O(W\times H)$。

填$dp\_map$和$dp\_path$表在两重循环中，计算次数$H \times W$，时间复杂度$O(W\times H)$。

回溯找最小能量路径和沿着seam删除像素都只与$H$有关，时间复杂度$O(H)$。

综上所述，总的时间复杂度为$W / 2 \times (O(W\times H) + O(W\times H) + O(H) + O(H))=O(W^2 \times H)$



- 空间复杂度

所使用空间包括：能量图，$dp\_map$和$dp\_path$表，seam路径。

能量图、$dp\_map$和$dp\_path$表尺寸都与原图像一样，空间复杂度$O(W\times H)$。

seam路径只与$H$有关，空间复杂度$O(H)$。

综上所述，总的空间复杂度为$O(W\times H) + O(H) = O(W\times H)$。



### 缩放前后图像对比



![](input.jpg)

![](output.jpg)
