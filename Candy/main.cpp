#include <iostream>
#include <cstdlib>
#include <vector>
#include <deque>
#include <map>

using namespace std;

struct adjvex{
	int id; int indeg;
	struct edge *first;
};

struct edge {
	struct edge *next;
	struct adjvex *v;
};

typedef struct adjvex adjvex;
typedef struct edge edge;

inline adjvex *adjvex_new(int id) {
	adjvex *v = (adjvex*)malloc(sizeof(adjvex));
	v->id = id; v->indeg = 0;
	v->first = NULL;
	return v;
}

inline edge* edge_new(adjvex *v) {
	edge *e = (edge*)malloc(sizeof(edge));
	e->v = v; e->next = NULL;
	return e;
}

void add_edge(adjvex *u, adjvex *v) {
	edge *e = edge_new(v);
	e->next = u->first;
	u->first = e; ++ v->indeg;
}

void adjvex_free(adjvex *v) {
	edge *e = v->first, *p;
	while (e) {
		p = e; e = e->next; free(p);
	}
	free(v);
}

vector<adjvex*> vertices;
map<adjvex*, bool> m;
deque<adjvex*> q;

int candy(vector<int> &ratings) {
	vertices.resize(ratings.size());
	m.clear();
	for (int i = 0; i < ratings.size(); ++ i) vertices[i] = adjvex_new(i), m.insert(make_pair(vertices[i], false));
	
	for (int i = 1; i < ratings.size(); ++ i) {
		if (ratings[i] < ratings[i-1]) add_edge(vertices[i], vertices[i-1]), m.find(vertices[i])->second = true, m.find(vertices[i-1])->second = true;
		else if (ratings[i] > ratings[i-1]) add_edge(vertices[i-1], vertices[i]), m.find(vertices[i])->second = true, m.find(vertices[i-1])->second = true;
	}
	
	q.clear();
	for (auto iter = m.begin(); iter != m.end(); ++ iter) {
		if (!iter->second) continue;
		if (iter->first->indeg == 0) q.push_back(iter->first);
	}
	
	int result = 0, count = 1;
	while (!q.empty()) {
		auto end = q.end();
		for (auto iter = q.begin(); iter != end; iter = q.begin()) {
			result += count;
			for (edge *e = (*iter)->first; e; e = e->next) {
				if (-- e->v->indeg == 0) q.push_back(e->v);
			}
			q.pop_front();
		}
		++ count;
	}
	
	for (auto iter = m.begin(); iter != m.end(); ++ iter) {
		if (iter->second) continue;
		result += 1;
	}
	
	for (auto iter = vertices.begin(); iter != vertices.end(); ++iter) adjvex_free(*iter);
	
	return result;
}

int main(int argc, char **argv)
{	
	vector<int> x = {3647,2304,31,4739,4342,3536,4742,4790,721,3090,3748,4526,2265,257,4408,3513,3007,3881,707,2077,2355,240,466,3321,4479,3502,3370,739,266,4800,329,3914,3456,360,5,4151,248,1099,293,969,4189,4041,496,1454,650,1256,1319,3657,137,2027,734,3845,2267,2553,3518,3098,1055,1888,190,2674,1689,519,2940,1497,880,2945,648,1128,4044,941,3450,4585,1334,298,1039,1985,1554,3710,642,1691,737,2729,536,4357,282,4055,3807,2689,2295,3997,363,336,4517,3303,1834,1749,2600,2482,2877,2996,3424,2679,2581,4758,2977,4972,3095,883,3683,3738,2575,4420,1467,4463,129,3101,4870,3937,790,3518,2934,1154,3854,3803,809,688,552,3410,3171,4782,2758,2947,2461,340,4057,1791,312,2153,2674,3995,2243,1601,4768,3710,2417,4897,1811,3639,186,3953,2157,4473,107,1012,3276,2269,1700,3829,2031,1223,4963,4789,522,2424,1481,4580,567,3146,3085,3242,3493,328,4843,3261,390,3612,4511,2201,2252,4697,1154,4409,4170,2614,421,3799,4883,3474,3980,3266,1049,3943,3055,1572,2719,889,2504,3287,4035,589,1529,2528,917,2724,2142,1307,2689,1653,4860,4941,2702,2366,4350,3225,4980,1124,2024,1215,950,1004,833,1999,1299,3889,4923,4018,1130,2427,2305,165,3016,186,2693,285,4263,1187,1592,1952,2840,2804,1893,1895,171,2595,1472,1503,71,3496,4071,1021,852,4904,4373,3503,145,648,2521,1275,3076,1179,2792,2444,1365,1838,2730,628,3025,674,2580,2218,4831,825,4113,2,3421,585,2857,4844,433,1928,2218,2637,1833,1591,1140,3330,2239,13,4606,1667,1192,3750,464,2558,588,3194,4538,3614,220,3471,832,51,4296,1297,1405,4069,3234,4263,3914,19,2543,1132,4008,4376,4075,148,4059,2666,1513,17,686,2706,3767,1150,1616,4356,4344,1154,4322,916,4625,154,2320,274,2803,3725,4343,1037,4340,4609,1056,1884,2093,1416,2612,1168,2916,1671,187,4429,3040,873,2135,1808,2023,103,2516,2719,1258,1838,4987,2235,3344,2307,2509,1147,2385,3205,3536,1725,4166,944,4961,2612,2360,2574,3780,276,597,319,4705,3638,1192,3193,446,4567,3296,2962,2286,906,1152,3626,3142,4496,933,2003,643,3318,1560,4179,1396,2079,123,1357,4691,2483,283,4823,4111,881,143,3816,4519,2687,2009,1317,2255,1658,631,893,2564,3135,4519,2058,2631,1805,4062,4626,1475,1974,3805,2871,4053,280,581,3744,4115,864,3568,3226,3097,63,3394,3968,2750,1756,1637,1357,3414,3620,3603,2330,1755,4474,4389,4386,1279,4803,4012,4107,1777,4169,1978,2183,801,3911,2279,1268,1128,847,4494,4225,2262,4241,3194,1365,997,1183,2722,763,4804,2677,3093,1559,2152,3834,946,4783,3637,1310,3890,1767,1832,2221,3950,2633,1132,1229,3902,2260,3429,4748,2838,2043,3989,2384,3408,1338,3567,1131,2101,3371,160,1547,4931,2312,381,2229,2096,371,4891,2338,3490,1723,4559,2440,4357,692,21,4611,4304,4802,4359,2142,1846,3349,4526,1606,1039,3094,4089,3141,2817,4250,1040,4100,1562,2773,2681,10,3144,2573,2349,1634,4296,3260,426,5,304,1800,4616,4609,2954,3976,1751,4800,3677,2630,2759,4716,2076,1848,4209,1245,1098,249,346,4013,3023,3027,375,2519,1952,4076,506,2601,2337,932,2606,2641,4084,3575,2250,2039,3903,354,3191,2580,4336,950,3648,2764,2799,4210,4009,249,811,4355,4262,3834,3735,4638,2706,2039,3714,3212,4640,2403,496,3599,45,4581,2174,3647,1620,1077,353,4811,9,4689,2114,9,2453,4913,4219,1463,162,31,2170,777,217,2257,415,2923,4297,481,2487,289,2885,2984,3888,4282,3917,1062,2929,1889,3491,4635,1700,4852,676,166,4862,4482,79,4081,2297,1594,464,4467,2371,682,3077,4138,4957,2374,4619,3797,2663,3856,3133,2904,3138,2050,3966,2420,3939,3810,3407,1991,3662,4083,2158,3524,3565,3589,3958,862,183,4422,1682,3906,1456,4759,3044,2766,3485,4016,1563,2500,2872,4696,404,2363,3098,723,1135,3389,4533,894,380,3195,4977,3890,3072,4895,2480,2030,757,4015,1452,3791,2922,4261,3550,2318,2027,3387,1334,4942,888,559,990,2644,4274,4088,3367,1761,2477,4252,2655,4209,2448,3984,3100,520,3879,580,3902,989,4595,354,1132,3869,967,1035,1188,2994,4422,2522,4288,1662,4433,278,4307,3707,4366,4026,1820,3195,3279,4475,2405,2079,4812,505,2599,43,2437,1501,2384,3384,3207,3517,2254,527,4552,4794,4873,3974,3668,4162,1989,3102,4440,2648,3161,159,1674,1334,4706,4953,2161,3463,3384,1973,3968,2335,2017,2757,188,4401,2494,3396,4270,1100,275,3822,894,148,4149,4562,4310,1138,4016,103,3786,3530,1614,460,4864,1320,1766,2025,4784,1502,351,104,3838,2368,4214,4026,3121,1708,3774,2392,2808,4049,2566,54,4198,1715,968,4860,4205,4985,1315,2991,4867,4281,4804,1083,1954,2922,3108,1738,4424,4811,3194,3262,2179,3760,2289,1653,468,1063,397,4628,1465,4315,4682,2015,1031,2003,3227,236,3340,4543,4580,3207,3824,736,4290,2130,3658,3750,3868,4434,3562,3415,2697,2093,2175,1338,98,3996,3753,1847,4976,218,1163,1011,2233,3546,3014,461,134,1354,1356,4714,913,1532,450,203,3663,460,305,3883,4895,219,3650,3944,2313,2178,282,3763,2526,387,611,2502,606,3126,3513,4191,1672,2879,1004,1806,4233,3712,2873,1498,245,3323,1701,260,3784,3359,495,31,3578,4146,3975,2243,1324,4257,1007,3850,4644,2970,2704,1602,1096,2570,2146,4120,449,3150,926,1035,1863,3799,2533,3460,3475,587,72,2259,298,567,2290,3876,1065,2617,2472,3741,1874,4831,3943,2870,2801,1648,4473,249,4218,2971,4369,1019,1121,1647,2054,4336,447,940,4148,3922,2879,572,2533,3177,1140,1175,3405,3557,3792,877,2299,2018,2060,1242,4888,4861,2890,713,1462,3460,3684,2183,4480,1158,3831,2886,1846,630,178,2347,904,3057,2919,4789,1234,411,964,4640,3969,1108,1869,1268,4478,3930,2510,718,143,1753,2784,1606,213,1468,141,4693,3978,3972,3932,2177,954,4110,4524,1858,2168,2443,1647,4754,2855,3963,746,1824,1423,2616,4444,901,1546,1954,1620,3041,3707,4404,999,273,2224,1141,4966,2555,1465,250,4732,2420,4361,4256,630,2881,3051,2278,2635,2258,2593,3382,434,4017,2350,4878,1270,248,3185,2890,3289,1892,3646,4289,2165,2223,430,3484,4778,1895,86,4510,667,4447,118,1298,3680,4521,4928,2668,1780,2521,2402,3566,2890,4752,3445,4161,0,1630,2051,3289,4874,2050,2578,3392,4273,4360,3228,4051,2608,3314,4913,3275,4114,1383,925,2794,2256,853,1814,4036,4727,4216,3955,2617,3968,2400,1778,320,382,182,3610,1608,2232,2540,1352,1505,1901,4580,1908,861,4247,3173,488,3361,4556,1414,2507,1812,3619,674,2201,3346,4890,1156,2316,211,4908,446,531,1642,628,493,3250,4212,3034,955,2069,1287,535,3977,2148,1134,2150,2636,847,3058,402,4707,1223,4022,381,4776,3720,271,932,2388,482,2192,2835,2366,3834,3463,2859,3436,4028,893,4391,1097,3532,1279,1427,680,3765,4929,4669,4613,2988,71,4320,563,445,1053,339,518,1324,2623,2906,3159,4815,2093,525,1,1909,4736,4789,937,1982,533,2034,514,1812,3461,2547,1929,4743,2216,1542,2731,3639,2214,4646,437,3267,4985,2307,944,2608,213,455,3775,2307,2332,3776,4216,2068,4917,1505,4050,450,4891,917,3614,3353,3464,544,3096,2032,3438,2179,2023,2005,1825,3812,272,3162,1119,2568,770,1333,4375,897,4992,1707,1025,560,128,942,3417,530,1393,3308,1447,7,3013,1263,551,2461,3295,342,4640,1671,2347,2817,483,3971,979,1603,1540,3101,4288,915,3998,632,3975,23,2544,4103,966,961,4633,3711,4269,2433,3718,2283,3696,622,4744,1992,964,737,15,3311,3554,498,2282,886,2101,174,339,2741,2442,690,3373,1417,2065,917,520,4383,1878,1505,3094,1148,3938,3165,4783,2635,3787,4527,979,1103,264,994,766,171,1492,4400,1057,4946,4575,2748,4039,2017,3438,2413,4786,504,4682,1658,1239,2913,3163,4334,413,3454,2499,196,1089,2638,4723,3420,3741,1340,4414,859,1511,2258,259,3920,3556,4834,3020,2596,3203,1459,1361,2989,3315,2395,4647,4554,308,4163,240,721,2617,4091,917,3706,3081,1993,2126,3174,4685,2892,4033,1196,1502,4293,1468,59,4127,4488,4007,3683,2299,368,1672,1966,2763,2672,2873,3072,1835,4465,145,4452,3557,2415,4510,1638,760,2988,4813,445,2232,198,2993,3734,4491,813,3793,4971,1653,2800,3654,3953,4520,1678,2271,3636,4350,144,3060,2537,4610,3205,3341,4519,1972,4203,2509,2732,2191,3674,3177,4423,3873,2522,4510,3364,3335,3303,3335,4989,2456,3341,294,3328,20,2565,1964,722,4062,24,4612,3672,3230,2953,4543,202,2157,2052,4287,700,727,2464,1476,4600,1339,986,4316,1026,641,4004,1015,4449,2345,2661,2778,3717,227,4742,792,4289,1119,404,4313,4349,4709,208,903,3218,2260,190,3919,4339,4007,1747,3939,1698,4085,4608,2724,4726,3612,3740,528,957,2753,3306,4675,2980,4400,467,3621,519,2223,4286,1220,1932,4494,2124,1503,3107,3666,1774,2446,4025,3521,2738,723,2606,2346,3448,3684,958,3540,4212,3267,1293,3870,4294,626,3271,1113,599,142,3336,1238,1363,1621,732,4839,3124,191,4857,4898,2638,3883,4771,376,958,2377,4074,758,2413,1384,4298,1626,4651,1944,1848,3946,3922,1471,59,4521,1614,4748,759,4329,1369,2844,4168,845,3035,377,743,2025,4260,514,3753,1571,4243,2827,2329,1656,4211,2980,4634,215,4924,2835,4161,198,4306,572,4719,920,1672,1831,1601,4393,1027,769,238,414,1147,2333,3792,1759,4199,2545,4682,4794,373,2012,1451,936,1344,2437,1151,1268,272,1664,2818,931,3589,3889,3203,261,720,4805,4655,3099,574,1245,4866,3073,3579,3658,1185,2778,1203,867,2573,2928,4231,376,3865,575,4165,1368,3195,790,4385,1013,1721,2974,4903,4924,3235,1975,1081,4242,1427,3008,488,1293,2433,4067,4951,3618,3197,2506,838,2122,435,1421,3850,652,3349,4368,3372,1544,158,2757,3910,3231,731,165,4507,319,3492,589,4561,1271,3597,1401,2564,1030,1820,3867,1001,1370,1374,3191,3492,1809,4612,3695,3813,4313,3063,2185,858,4573,4943,1120,2804,2026,2637,3663,2345,2481,4252,3259,3753,4201,1012,1317,232,2833,1537,2585,4203,2911,776,4047,1072,1740,2742,1237,1054,805,3422,3264,378,4717,736,4534,1744,3373,3198,441,854,3802,52,4607,3004,1065,2277,4588,250,166,2173,4453,3077,4301,3500,501,1041,2595,1738,3447,3400,160,3063,131,1230,3799,1017,2974,3524,4215,4767,731,3018,1172,1690,1022,2237,3967,1962,3839,4133,4135,3292,3562,3436,3144,4063,829,739,2153,4277,492,3666,3692,1975,4896,2492,2992,4222,1016,3560,341,1747,1578,1513,3438,3952,102,3757,914,3941,4243,1401,2233,4157,1189,1730,4573,2018,2469,1726,2647,4313,392,1340,1288,1640,184,4281,862,2552,2841,1204,652,771,4069,4090,1075,4172,4199,3341,3113,4794,4742,1699,3952,2283,3429,3525,4301,2250,1603,3301,1564,3348,993,2852,4988,1177,3485,2203,3729,2678,4759,4381,3449,3828,4823,876,4352,375,4217,2466,169,311,517,4121,3946,3946,3998,3248,2548,602,2901,4112,302,3894,3317,290,71,1802,3845,152,4481,3604,886,4282,3785,709,159,3137,1084,728,1955,2606,2392,2472,3079,1338,2770,2078,938,319,4032,3839,4431,4334,4085,4100,976,508,903,4822,661,384,4778,1547,1018,3563,3608,2529,3053,1045,3258,8,3651,2002,2481,3082,4692,251,1512,631,1922,544,822,2706,1230,4908,1806,3559,416,2709,3381,1077,4445,4511,3976,464,4427,2585,2993,2480,4982,2603,2488,3633,4605,1321,1715,650,1573,3228,1281,4847,124,2103,2553,2707,3363,4360,1266,3780,2069,999,1209,2867,510,1538,4683,4937,475,4028,2417,457,1632,1258,442,2589,2579,3509,3239,504,3089,872,352,3214,4328,2905,2273,2691,2265,3539,2823,687,890,385,4906,1400,1923,4589,2690,2398,3617,1459,4207,1601,2717,4649,4191,1649,3158,3782,2153,1248,4655,2505,814,3983,411,4439,1674,4028,4330,850,1067,220,1235,973,2972,3158,1914,662,1908,532,2122,1115,2133,1191,2116,2676,2840,274,1459,4994,2874,2466,3851,40,1449,614,4479,4475,995,161,325,2062,381,2912,4388,3354,1070,1302,4016,4330,3186,2490,445,1672,34,2561,4348,2874,4188,2159,4220,3414,4625,3072,3455,2426,38,4286,3254,1033,4448,4931,4448,1181,2844,3836,4535,266,1490,4904,4597,4677,2394,42,1349,2428,3956,2049,1655,3144,4209,875,1558,186,299,1365,3965,1690,2004,2219,2723,2804,2150,2171,3985,1346,2359,3521,1613,3850,3425,1210,3527,2171,1252,1228,4600,1560,3277,2607,4704,3838,3482,2615,4025,134,3980,4342,1824,984,1561,899,3788,63,4423,2774,2762,1782,2647,4375,1984,1072,585,1863,3243,3189,3091,4195,4750,1369,1802,806,207,1637,3421,584,3123,2402,1278,4947,4738,2839,2198,4879,4255,1621,4005,3369,4756,1652,2744,3092,4076,4681,4956,2319,4222,4399,2867,324,2120,1021,1131,3680,2658,4552,4264,781,3306,543,2080,4397,4734,631,4276,341,3604,3281,62,4712,4933,2806,2805,4009,3839,4113,2680,4414,3512,1899,4738,633,2921,2221,4313,1931,3126,4929,4065,1432,1824,1145,829,2911,3128,1457,4604,1733,4738,4667,1445,4671,3825,602,32,2665,4715,4065,2079,3228,964,3169,213,237,391,878,2169,3517,807,1234,1301,3984,3731,2131,1895,1860,3588,1499,3593,4679,2518,1390,702,1344,1993,2087,4009,1708,1152,2440,1288,2116,609,1501,3706,2352,3731,875,869,4539,2109,2171,4875,840,654,3122,4052,594,973,3997,273,3492,388,2328,4836,3733,4415,197,441,567,3989,3082,4035,950,935,2741,3303,4667,3616,4172,558,2077,2695,433,4270,3349,3555,3322,3944,4528,2320,569,4372,4060,2897,4208,2793,2312,757,4586,4231,4746,2668,3267,697,4956,2360,352,4623,977,4524,1533,4406,3572,1966,3676,1921,1873,3351,2217,2753,2023,2787,2126,1083,2036,2686,228,4349,3444,4814,4932,4542,3835,3199,1591,143,560,1943,4766,2889,2820,2651,3647,1392,969,2324,4665,2842,675,1883,1947,2698,1022,425,133,3058,3112,361,3759,2908,1527,3692,2450,1714,3243,394,1857,155,3689,2975,4396,2861,626,3044,605,1595,1720,271,789,2395,3506,2737,1445,880,3162,2930,3938,2626,4643,4050,534,1170,4094,4337,4237,3689,1083,1094,3845,4772,422,3241,3986,1048,2637,4591,3996,4357,1214,4785,3104,4720,3874,901,600,3389,3831,891,1015,3474,1293,2902,997,387,3591,234,428,4674,2680,4273,798,3102,3867,4784,4151,1504,728,4499,862,1942,4284,318,3015,4511,1220,4967,4252,51,2210,1619,4878,3503,4521,875,242,4464,1109,671,4138,3789,1296,1289,1892,163,1073,2395,3020,1801,1894,3882,96,2530,552,3111,3393,1772,4430,2645,1824,1641,4265,3054,1496,138,3929,1739,955,38,3762,93,179,58,1382,3423,1574,3808,818,4594,1961,4064,4828,2057,2947,380,1520,1340,2153,951,338,329,2592,955,3383,4088,1093,2312,2179,3400,3702,941,3494,233,2352,1228,3657,278,1388,827,4872,3350,1244,4700,1759,4191,1432,4632,1883,3585,583,2221,266,4527,3176,1,4967,622,3665,2147,4022,2367,4440,3868,3953,3144,1449,3962,3422,4189,1141,3294,3891,3737,4346,651,2928,779,283,1164,716,2218,3385,2335,1745,2914,2336,1712,4888,1002,211,3910,4721,4652,4131,3674,2796,580,3988,1219,1121,130,865,13,3867,212,664,3148,2343,2299,4312,3059,869,4049,394,2614,3315,4083,678,3203,85,890,2114,4806,1894,2597,4833,1042,4529,3821,2261,650,303,4479,663,4171,1043,2679,3671,3386,4978,4335,2797,847,4736,4544,4813,3052,3627,1844,1255,3712,2734,4721,3518,980,2318,4703,2022,1847,3525,4284,2498,180,115,3161,703,1158,841,4374,4544,2171,61,2341,4371,4798,1885,536,2850,512,2380,457,576,1466,179,447,2446,3849,150,4469,697,27,105,4547,208,220,4060,911,1378,1253,1638,2274,4777,1699,967,4148,1497,4205,4684,699,4717,3417,2509,1646,4883,2688,2093,2330,1537,3595,1799,3586,3623,1904,4485,183,3476,3546,1094,1206,4799,2732,3480,4576,784,4447,76,3633,3652,1113,4333,4722,4530,1842,2720,4413,882,4813,3095,3771,3408,4894,3710,3383,3150,3195,3566,2978,1741,1013,4184,2893,97,4016,2469,881,3464,3898,4515,3468,11,200,4542,4541,3394,2262,306,4276,3427,4754,4399,3188,1000,3109,2923,4151,1305,1490,3481,4398,3855,2666,2291,3952,1682,1113,4834,1498,11,701,1319,22,901,861,915,4295,4476,2573,4923,4255,2327,4322,2443,3328,3784,367,3831,1441,3209,2312,839,2064,4978,3131,1016,3013,596,2202,863,607,2903,2182,1981,156,4396,2896,4451,3872,469,726,4479,4149,1401,1923,2477,185,3642,1308,2978,1851,3620,3817,267,4951,3300,1283,4316,3896,4838,179,4503,2741,2362,2836,2898,1758,732,3701,1982,2554,780,2813,1703,2181,4736,532,3718,4730,3192,1696,2933,1812,1865,3200,3115,166,836,2431,4062,674,3963,4918,4767,1325,4106,4017,4435,4839,2719,2769,3745,3499,582,1800,2032,1671,3684,2102,1401,1876,3798,687,40,663,239,3156,2181,1075,1939,2596,3101,902,3866,4221,3579,2972,3238,3014,4163,2309,2135,2908,2160,2718,1060,4192,4389,4744,2646,2142,1620,1444,2829,3013,3460,4421,1169,1993,1848,4460,4589,4950,1715,3455,523,294,2780,113,4661,1943,2423,1796,1204,935,4514,3616,1480,255,3361,4126,2398,1333,571,1579,4346,383,1000,1867,2376,2849,2680,3318,4151,4395,1773,4674,4689,905,4787,4350,2849,3562,1147,405,4498,661,4021,978,2269,3734,1456,4667,1420,3379,1246,2118,3762,3599,3986,2491,1448,3018,809,1951,2413,3934,2977,2102,4840,4116,2805,4041,2679,3952,4446,3529,965,3467,859,3234,3554,2315,4253,4974,695,1852,2092,809,451,2430,3300,3251,448,461,202,2861,4396,3179,1316,588,2295,4121,4629,1326,4425,427,4855,1742,246,2066,4977,3800,4382,582,3774,1429,2434,2219,2238,4237,4649,539,2488,1450,1000,4042,663,1748,2221,3331,2336,869,2452,3317,2195,3229,3744,3403,4972,343,469,1301,4143,1203,1883,4270,2632,670,1489,4871,4907,2490,1762,2396,292,4114,1438,956,863,12,639,4551,2233,4444,4221,4428,2673,4317,4183,3997,4660,1005,298,3804,3560,3534,4426,1193,4204,915,2416,4111,4757,530,2859,50,4644,650,2358,1859,2014,2997,2763,4247,2441,1984,27,1467,1301,563,464,962,1568,763,1118,128,649,544,2673,4853,2811,1441,316,2568,1971,4528,3970,2968,1530,2680,1179,3544,678,3942,4143,4471,2278,4170,938,3580,4733,2755,894,2653,4870,3364,4134,519,260,1807,1724,3071,3249,2040,1991,1572,2920,2314,4540,4450,4994,2072,4346,672,1014,3489,1496,3293,4012,3786,3225,97,1541,471,2751,1411,187,3237,1930,447,44,6,4870,4645,3399,3213,2570,1319,527,3462,2122,522,534,1468,2546,2901,1310,4042,2546,322,4181,2123,1771,722,3946,4522,3486,4133,4111,1768,932,508,1775,2154,1505,174,367,4075,1493,895,2538,3615,2769,4424,1436,315,2325,2746,710,4871,4420,4891,3346,1191,613,2292,2066,4099,1425,1177,868,3709,1685,2643,863,3191,4169,2583,2266,662,4830,1156,630,2599,1933,2066,2914,4258,1164,3624,482,584,3515,3828,1775,481,1121,3841,4580,3898,1371,1800,3960,3056,795,1175,2599,4964,3758,1218,1979,3588,2374,3961,1187,659,2379,454,4918,3543,4078,1752,479,3946,580,3606,4427,3053,2448,359,3304,171,3512,2264,3227,659,3439,2179,1976,3550,3397,3955,3490,2123,2916,1030,2783,295,1484,2701,190,1914,805,669,2212,2737,4275,1639,2143,3075,3351,447,4598,3215,4063,2826,3874,3854,1357,850,2404,4754,1157,895,1877,425,1925,4660,2072,4761,3713,2262,1675,4518,4283,3888,3608,4911,1879,751,4338,1582,1198,3937,1149,261,3115,1376,467,4472,2226,2872,4226,4736,119,2455,161,3396,3468,2234,4509,2181,848,1184,3052,1484,1424,1660,2747,4656,2411,3437,2590,4961,2374,3740,1574,1841,116,2041,1313,3694,1265,1891,3430,2736,699,4944,2484,4167,3530,1993,1348,730,4530,752,3566,954,2412,1313,1962,1175,4751,905,1136,3477,4645,2710,319,1113,1104,2984,1159,2369,1228,4590,106,1927,886,2590,1094,4416,4584,3794,1498,466,4547,65,2772,3311,1378,4735,4487,2481,640,623,959,1637,4686,2630,4102,790,614,261,4511,1842,4851,4617,3769,2089,3560,1215,2857,4496,10,4356,4962,4557,4421,2734,2868,2151,3821,2355,4633,813,4331,1944,2450,369,4574,1552,1159,188,1814,670,3383,3017,1640,3504,1459,1552,4720,4316,1048,4730,3672,2362,4287,4445,1448,3507,1597,270,2215,2582,2435,1546,878,4886,3267,452,2790,4426,1992,956,1448,375,326,4440,232,1785,992,4952,2453,3392,4682,1126,754,321,1923,3555,180,4872,177,2395,3806,2612,293,4684,3850,3560,136,2993,4338,3481,3949,787,208,627,227,440,3764,1220,392,1218,964,1426,3696,3071,3099,619,1626,3280,492,1803,675,4298,767,969,335,4618,881,471,2611,220,304,1560,1007,513,3540,2586,2305,2304,3806,4050,3522,1123,476,2218,4194,3576,4190,820,1856,1034,3975,3883,1684,4742,4852,2019,4360,734,3843,1971,2306,4147,4884,3313,1012,4776,899,3318,2080,1058,3720,603,2181,4196,4173,1375,4124,4715,3547,2332,749,3874,1216,2434,3616,2420,4453,4329,4506,3296,1300,1812,3796,2536,125,4808,2312,2377,4478,745,3435,3198,2700,1968,3747,3225,4695,2871,2941,4594,1556,3690,3468,2772,1124,2084,192,1930,1413,1051,226,4066,2863,4022,2954,4341,183,1619,1718,4661,2364,1505,4212,1416,4825,4311,4641,4520,2182,2582,4114,90,1273,3934,2862,3749,1018,4407,679,3784,458,906,4202,3321,1280,2156,2662,1463,127,732,2477,2491,2237,3041,3907,3414,2352,3549,2934,886,2483,3400,977,3756,3686,3839,2506,4705,4598,4537,4841,56,443,4043,4730,3076,2551,3744,891,2679,829,3368,1522,3066,1409,430,2833,3761,331,767,4648,2814,520,1977,2923,4206,816,1781,263,1767,1318,1456,1823,3114,499,2905,1190,4403,1650,3433,2082,3831,1802,3604,1897,4563,386,1082,4677,2069,1850,677,1236,3722,2654,4159,4280,4822,2292,4544,1589,3610,2352,4765,3076,2852,2670,618,2255,672,4052,689,4503,2206,4293,2753,1769,1032,3835,2798,3101,2037,3475,4337,2111,2481,4848,1392,2304,2140,2288,3893,2103,4640,3658,179,3844,2681,798,1099,3353,1202,1788,4209,3408,2434,1962,1529,3466,2149,4328,1567,4187,4155,2257,1298,1637,2105,4042,3941,598,1330,4186,2701,971,2845,4232,4815,1878,1382,2267,231,2584,407,792,2344,2841,2754,3874,2659,1256,4554,579,443,3709,2836,3093,1698,1293,2136,639,3243,4818,1178,2296,2141,375,1529,3309,2253,4263,576,3836,1848,2335,4629,4192,177,3735,4418,4188,4991,3972,4767,1786,4034,3955,1232,732,1601,4720,2724,4844,4538,3902,2141,3032,629,22,1341,2882,4285,1917,1718,2485,4252,2699,3030,781,2787,2448,1322,2778,2773,1089,917,1807,1397,3501,2539,2998,3221,1615,4194,4111,517,2687,2143,1146,4061,3484,380,3347,1753,3451,2184,2358,1150,214,4491,289,4015,813,4420,1788,3255,337,4947,4652,190,3838,4002,3411,454,4548,3874,2323,2236,2370,4822,2649,854,202,2348,3960,5,4533,1318,2508,1099,2161,2797,1466,2975,2217,4606,1230,2554,4553,2234,4096,3392,2588,2507,198,2136,2734,2521,724,104,2343,3374,2310,3898,722,1270,3903,1607,3940,1411,2707,2454,4209,4173,429,1426,132,3011,333,4685,1597,4429,4429,4185,3289,4627,2673,1023,3501,4750,2479,2196,3124,4789,1094,198,2412,4998,1806,2704,2761,865,158,1970,1390,1939,4749,1522,1302,82,1208,2899,863,1989,3436,504,2969,1110,2879,1470,860,358,3666,336,148,1113,534,3912,2463,3692,1616,224,4557,3127,3547,2300,66,3296,3822,1369,4730,1382,620,593,3372,4057,2450,2693,1519,329,4163,2379,688,4181,4067,2188,1646,953,1100,4109,4646,4068,686,555,2195,4233,2855,3614,2529,1678,4983,2259,4412,603,4204,2784,1012,1654,477,2531,1984,992,1262,4024,1526,329,1212,3172,2635,3664,3634,2281,2732,4320,4188,1280,3553,2044,4894,2434,74,1229,1045,4486,3184,1601,3623,4197,4608,4100,3080,2944,1445,4343,1968,4323,1024,3180,3847,11,1844,2481,2292,928,3153,1481,2208,3058,4877,3454,492,4951,1035,2889,4437,4220,843,3060,4769,451,3513,2849,3395,1310,3544,1715,633,921,4895,4480,932,3091,3314,4577,371,1467,2410,3932,4526,2287,2386,1370,3590,3422,612,4379,3994,1455,3792,115,1906,2305,2964,1653,4967,2861,3368,600,134,4615,1432,2418,4058,4746,3347,4429,2566,757,3361,3444,4396,2100,1166,4338,1874,1778,3718,868,4585,2510,983,2843,1167,299,4496,1134,4512,4216,3086,998,3831,870,3417,2889,617,1764,3671,4535,3874,2032,2979,4622,484,497,3961,2358,2276,2679,4578,3213,1541,1913,1057,2708,2213,553,194,3077,4770,3280,4076,4953,4150,3845,4195,1119,1961,2866,2006,835,4898,4985,1810,1735,483,771,4093,4111,3450,3672,2324,4991,585,3381,4051,4150,287,4245,3580,1409,3877,2656,2714,3027,1501,1909,499,4814,4775,2505,2002,1026,3843,3812,2761,678,4583,3206,1141,4385,3230,3465,4376,168,3199,4779,4318,4838,4024,2898,2599,2901,1906,313,2280,4759,2223,2779,4574,3350,1637,1576,4376,480,388,2137,1158,1323,1696,2299,708,4926,2116,1436,94,1667,1215,4413,1505,239,3663,456,4492,1922,770,1772,1681,4345,904,2607,2695,2541,535,2072,4373,2275,561,531,3598,2257,4182,4306,2184,2650,742,3630,4318,3309,4395,2175,4900,4411,2632,4392,1333,4754,2517,3014,4099,3421,1974,1794,2314,2509,218,1687,4785,780,2218,3383,4389,2752,4042,2925,402,1136,1556,1072,4446,951,3248,4346,362,2232,3739,3047,1986,1256,1062,1085,1029,4388,2879,3343,1897,3098,30,1682,230,3600,1418,971,2704,460,3897,3106,2948,1805,4179,2394,2756,3779,1741,4471,1011,1832,2518,2997,4440,4932,4082,1821,4320,3313,164,2570,2763,1546,604,4345,146,2022,317,2850,3834,4214,2308,1783,1019,2839,4177,127,1618,2270,950,3981,454,4821,3330,1246,1105,3764,3067,1778,2078,4583,4348,1193,1129,4952,539,1275,3327,2208,477,3513,2774,4138,296,3793,1977,826,272,4948,4448,2575,3929,1255,2396,3612,2501,3501,2376,1921,279,4454,1504,979,2000,2634,2284,3891,261,611,1099,2091,4124,3873,1229,773,4018,4558,2951,642,4506,2399,3217,4788,3654,613,3400,2508,467,776,4429,2098,1583,933,3078,4935,4919,362,3826,1533,2325,1277,3624,2801,150,4853,4926,520,763,2877,1162,270,277,732,1410,283,2697,1162,2791,3164,3290,3572,263,1225,858,4693,1160,777,1407,4986,2310,84,2615,2286,4237,4117,3491,4164,4637,4255,2041,2152,877,2318,2884,3639,3954,1933,4801,1745,98,4443,318,1713,669,2528,2758,1829,3305,4165,3168,1968,601,783,4254,4838,4901,2746,4002,890,3353,1044,4394,4230,4714,3630,2869,3668,564,4022,1766,2014,3465,3436,3727,4134,964,2837,2316,621,3354,484,2589,3955,2619,3196,3793,3872,2294,4148,1115,647,192,509,1229,1258,4140,4098,1279,1056,3120,3045,3070,2937,1481,3149,2072,3797,986,740,4418,4340,2576,3360,3295,195,1556,3440,420,3850,2588,1535,849,4132,3396,2078,391,2536,1176,3022,4944,648,1067,3014,3585,3900,2515,2009,2697,3501,2749,3467,4193,325,1827,3840,1873,3383,3633,2293,3585,1221,180,786,1706,3576,2864,3449,1113,392,1471,2409,2392,2538};
	vector<int> y = {1, 2, 2};
	int result = candy(x);
	cout << result << endl;
	return 0;
}
