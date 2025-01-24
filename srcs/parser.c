#include <../includes/cub3d.h>

// typedef struct s_tex
// {
//     char *path;
//     bool appear;
// }t_tex;

// typedef struct s_color
// {
//     int red;
//     int green;
//     int blue;
// }t_color;

// typedef struct s_map
// {
// 	char	**mapinfo;
// 	int		width;
// 	int		height;
// }t_map;

// typedef struct s_config
// {
// 	t_tex   path_NO;
//     t_tex   path_SO;
//     t_tex   path_WE;
//     t_tex   path_EA;
//     t_color floor;
//     t_color ceil;
//     t_map    map;
// }t_config;

t_config *parser(int fd)
{
    t_config *config;
    config =(t_config *)malloc(sizeof(t_config));
    ft_memset(config,0,sizeof(t_config));
    //一行ずつずつ読み込む、読み込んだら種類を判断してconfigのメンバに格納する
    return (config);
}