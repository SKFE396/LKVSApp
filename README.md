﻿# LKVSApp
The application for developing and testing LKVS virtual file-system

## 简介
*    LKVS是一项虚拟文件系统服务，它用于将单个文件解释为一个磁盘，并提供基础文件储存服务。
*    LKVS底层调用文件系统接口操作虚拟磁盘文件，并向调用者提供虚拟文件系统接口。
*    设计LKVS的初衷是为了整合零碎的文件，并且在无需解包的情况下对这些文件进行基本操作。

## 特性
*    LKVS支持动态扩展磁盘大小。当虚拟磁盘文件内部没有多余的空间用于储存新写入的数据时，LKVS将自动扩大虚拟磁盘文件的大小。
*    LKVS支持超长（小于2^32个UTF-8字符）、包含任意字符的虚拟文件/目录名。

## 说明
*    关于文件格式
    LKVS包含一套完整的文件格式，整个虚拟磁盘文件的内容需由LKVS完全管理，调用者不应通过除LKVS提供的接口以外的任何接口修改文件内容，否则可能导致虚拟文件系统结构被破坏，或私自追加的数据被LKVS的写入操作覆盖。如果想要为虚拟磁盘文件附加识别信息，可通过自定协议，利用LKVS在虚拟磁盘内部创建文件以储存识别信息。

*    关于储存机制
    为了储存能够动态改变的文件并且提高执行效率，LKVS使用和文件系统类似的模式进行空间分配管理，即以簇（块）为单位进行空间分配。这种模式会在一定程度上造成磁盘空间的浪费，但这是无法完全避免的。
    因此，尽管LKVS可以用于创建存档以打包多个文件和文件夹，但不建议将LKVS用于制作静态存档，因为各类压缩软件提供了更高效的解决方案。
    另外，基于簇（块）的空间管理，将会导致当虚拟文件被删除或截短后，在虚拟磁盘中留下磁盘碎片。这些磁盘碎片将占用文件内部的空间，使得磁盘空间的使用率降低。添加新的数据时，LKVS会优先将新的数据写入这些碎片中以重新利用空间，但LKVS不会通过自动移动虚拟磁盘数据的方式减少碎片。如果虚拟磁盘文件存放在机械硬盘上，则无论硬盘本身的碎片还是虚拟磁盘中产生的碎片都可能导致读写效率的下降，但二者带来的效应不会叠加。储存在固态硬盘上的虚拟磁盘文件，产生的碎片则不会造成读写效率下降，仅仅降低空间利用效率。如果希望在机械硬盘中提高读写效率，则需要同时清理机械硬盘和虚拟磁盘中产生的碎片。
    当前版本中LKVS未提供专门的清理碎片操作。在储存空间允许的情况下，可以新建一个空白虚拟磁盘，并复制所有文件到新的虚拟磁盘中，由此得到的新虚拟磁盘将不会含有磁盘碎片。
