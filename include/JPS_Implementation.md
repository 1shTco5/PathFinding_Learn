# JPS算法ACM风格实现指南

## 学习前提确认
- ✅ 已阅读JPS论文，理解基本原理
- ✅ 熟悉A*算法概念
- ✅ 具备C++编程基础
- ❌ 尚未查看JPS源码（保持独立思考）

## 渐进式实现路线

### 问题1：基础网格A*寻路
**难度**：★★☆☆☆
**目标**：复习A*算法，建立基础框架

```cpp
// 基础数据结构模板
struct Point {
    int x, y;
    // TODO: 重载必要的运算符
};

struct AStarNode {
    Point pos;
    double g, h, f;
    AStarNode* parent;
    // TODO: 构造函数
};

class GridAStar {
    vector<vector<bool>> grid;  // true = 障碍物
    int width, height;

    // TODO: 实现以下函数
    bool isValid(const Point& p);
    vector<Point> getNeighbors4(const Point& p);
    double manhattan(const Point& a, const Point& b);
    vector<Point> reconstructPath(AStarNode* end);

public:
    vector<Point> search(const Point& start, const Point& end);
};
```

**测试用例设计**：
- 3×3无障碍网格
- 5×5有障碍网格
- 路径不存在的情况

### 问题2：8方向A*寻路
**难度**：★★☆☆☆
**目标**：扩展支持对角线移动

```cpp
class GridAStar8Dir : public GridAStar {
    // 扩展功能
    vector<Point> getNeighbors8(const Point& p);
    double chebyshev(const Point& a, const Point& b);

    // 移动代价计算
    double getMoveCost(const Point& from, const Point& to) {
        // TODO: 直线移动代价为1，对角线为√2
    }
};
```

**关键思考点**：
- 8方向移动如何影响启发式函数选择？
- 对角线移动的特殊处理

### 问题3：强制邻居检测器
**难度**：★★★☆☆
**目标**：理解JPS的核心剪枝概念

```cpp
class ForcedNeighborDetector {
public:
    enum Direction { N, NE, E, SE, S, SW, W, NW };

    // 核心函数：检测强制邻居
    static bool hasForcedNeighbor(const vector<vector<bool>>& grid,
                                 const Point& pos, Direction dir) {
        // TODO: 根据JPS论文实现
        // 提示：分直线移动和对角线移动两种情况
    }

private:
    // 辅助函数
    static Point getDirectionVector(Direction dir);
    static bool isValid(const vector<vector<bool>>& grid, const Point& p);
};
```

**思考重点**：
- 什么是强制邻居？为什么需要它？
- 不同移动方向的检测规则有何不同？

### 问题4：跳跃函数实现
**难度**：★★★★☆
**目标**：实现JPS的核心跳跃逻辑

```cpp
class JPSJumpFunction {
    const vector<vector<bool>>& grid;

public:
    Point jump(const Point& start, const Point& direction, const Point& goal) {
        // TODO: 实现跳跃逻辑
        // 终止条件：
        // 1. 遇到障碍物或边界
        // 2. 到达目标点
        // 3. 发现跳跃点（有强制邻居）
        // 4. 对角线移动时的特殊处理
    }

private:
    bool isJumpPoint(const Point& pos, const Point& direction);
};
```

**算法思路提示**：
- 递归或迭代实现跳跃
- 注意对角线移动时要检查水平和垂直方向的跳跃
- 跳跃点判定是关键

### 问题5：JPS邻居生成器
**难度**：★★★☆☆
**目标**：实现只返回跳跃点的邻居生成

```cpp
class JPSNeighborGenerator {
    const vector<vector<bool>>& grid;

public:
    vector<Point> findNeighbors(const Point& pos, const Point& goal) {
        vector<Point> jumpPoints;

        // TODO: 对8个方向进行跳跃搜索
        // 只将跳跃点作为邻居返回
        // 注意：目标点总是被视为邻居

        return jumpPoints;
    }
};
```

**关键理解**：
- 传统A*返回相邻格子，JPS返回跳跃点
- 为什么这样可以减少搜索空间？

### 问题6：完整JPS算法
**难度**：★★★★☆
**目标**：整合所有组件实现完整JPS

```cpp
class JumpPointSearch {
    vector<vector<bool>> grid;
    int width, height;

    // 组件
    ForcedNeighborDetector detector;
    JPSJumpFunction jumper;
    JPSNeighborGenerator neighborGen;

public:
    vector<Point> search(const Point& start, const Point& end) {
        // TODO: 使用A*框架，但邻居扩展使用JPS
        // 核心区别：
        // - 邻居生成使用findNeighbors而不是getNeighbors8
        // - 移动代价计算需要考虑跳跃距离

        // 伪代码结构：
        // 1. 初始化open/closed sets
        // 2. while open set不为空:
        //    a. 取出f值最小节点
        //    b. 如果是目标，重建路径
        //    c. 使用JPS生成邻居
        //    d. 对每个跳跃点计算代价
        // 3. 返回空路径（未找到）
    }
};
```

### 问题7：性能对比分析
**难度**：★★☆☆☆
**目标**：验证JPS的性能优势

```cpp
struct SearchStats {
    int nodesExpanded;
    int pathLength;
    double searchTime;
    vector<Point> path;
};

class PathfindingBenchmark {
public:
    static void compareAlgorithms() {
        // TODO: 设计测试用例
        // 1. 简单网格
        // 2. 复杂迷宫
        // 3. 开放空间
        // 4. 狭窄通道

        // 对比指标：
        // - 扩展节点数量
        // - 运行时间
        // - 路径质量
    }
};
```

## 实现建议

### 每日计划
- **Day 1**: 问题1-2（基础A*巩固）
- **Day 2**: 问题3-4（JPS核心概念）
- **Day 3**: 问题5-6（完整JPS实现）
- **Day 4**: 问题7（测试和优化）

### 调试技巧
1. **可视化输出**：打印搜索网格，标记扩展的节点
2. **小规模测试**：从3×3、5×5网格开始
3. **边界情况**：测试各种障碍物配置
4. **路径验证**：确保路径连续且最优

### 关键思考问题
1. 为什么JPS能减少搜索节点数量？
2. 跳跃点的数学定义是什么？
3. 什么情况下JPS可能不如A*？
4. 如何优化JPS的内存使用？

## 后续扩展
完成基础JPS后，可以考虑：
- 双向JPS搜索
- JPS+（预处理优化）
- Any-angle路径平滑

现在你可以从问题1开始，每个问题实现完成后进行充分测试。遇到问题时，我会给出针对性提示。