#ifndef _HAL_PMU
#define _HAL_PMU

struct pm_ops {
    int32_t (*busy)(void *param);
    int32_t (*suspend)(void *param);
    int32_t (*resume)(void *param);
    int32_t (*suspend_late)(void *param);
    int32_t (*resume_early)(void *param);
};

#define M_PMU_SUCCESS               (0)
#define M_PMU_ERR_FULL_DEV          (-1)
#define M_PMU_ERR_DEV_NOT_EXIST     (-2)
#define M_PMU_DEV_BUSY              (-10)

int32_t pmu_dev_register(struct pm_ops *dev, void *param);
int32_t pmu_dev_unregister(struct pm_ops *dev);
 
int32_t pmu_dev_busy();
int32_t pmu_dev_suspend();
int32_t pmu_dev_suspend_late();
int32_t pmu_dev_resume();
int32_t pmu_dev_resume_early();

#endif /* end of include guard */
