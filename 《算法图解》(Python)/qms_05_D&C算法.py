"""
D&C, divide and conquer, 分而治之
（1）找出基线条件
（2）分解问题直至到基线条件

任务：有一块矩形土地，要用相同的正方形覆盖它
找到正方形最大边长（最大公因数）
"""


def find_side_length(length0, width0):
    if width0 == length0 * 2:
        return length0
    elif length0 == width0 * 2:
        return width0
    else:
        if length0 > width0:
            length0 -= width0
        elif length0 < width0:
            width0 -= length0
        else:
            return width0
        return find_side_length(length0, width0)


length = 1920
width = 648
print("土地的面积是%d * %d" % (length, width))
print("覆盖土地的最大正方形边长为" + str(find_side_length(length, width)))
# while 1:
#     if width == length * 2:
#         side_length = length
#         break
#     elif length == width * 2:
#         side_length = width
#         break
#     else:
#         if length > width:
#             length -= width
#         elif length < width:
#             width -= length
#         else:
#             side_length = width
#             break
# print("覆盖土地的最大正方形边长为" + str(side_length))
