#ifndef _TBF_H
#define _TBF_H


//创建令牌桶
int tbf_init(int cps, int burst);

//取令牌
int tbf_fetchtoken(int tbf_id, int ntokens);

//还令牌
int tbf_returntoken(int tbf_id, int ntokens);

//销毁指定令牌
void tbf_destroy(int tbf_id);

//销毁所有令牌
void tbf_destroy_all(void);

#endif
