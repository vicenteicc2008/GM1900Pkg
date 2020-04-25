#ifndef __I2C_QUP__
#define __I2C_QUP__

typedef enum {
    I2C_QUP_DEVICE_TYPE_GSBI = 1,
    I2C_QUP_DEVICE_TYPE_BLSP,
} i2c_qup_device_type_t;

struct i2c_msg {
    unsigned short addr; /* slave address */
    unsigned short flags;
#define I2C_M_TEN 0x0010          /* this is a ten bit chip address */
#define I2C_M_WR 0x0000           /* write data, from master to slave */
#define I2C_M_RD 0x0001           /* read data, from slave to master */
#define I2C_M_NOSTART 0x4000      /* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_REV_DIR_ADDR 0x2000 /* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_IGNORE_NAK 0x1000   /* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_NO_RD_ACK 0x0800    /* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_RECV_LEN 0x0400     /* length will be first received byte */
    unsigned short len;             /* msg length */
    unsigned char *buf;             /* pointer to msg data */
};

struct qup_i2c_dev {
    LIST_ENTRY Link;
    int        id;

    i2c_qup_device_type_t device_type;
    unsigned int          gsbi_base;
    unsigned int          qup_base;
    unsigned int          gsbi_number;
    int                   qup_irq;
    int                   num_irqs;
    struct i2c_msg       *msg;
    int                   pos;
    int                   cnt;
    int                   err;
    int                   mode;
    int                   clk_ctl;
    int                   clk_freq;
    int                   src_clk_rate;
    int                   one_bit_t;
    int                   out_fifo_sz;
    int                   in_fifo_sz;
    int                   out_blk_sz;
    int                   in_blk_sz;
    int                   wr_sz;
    int                   suspended;
    int                   clk_state;
    unsigned int          noise_rjct_scl;
    unsigned int          noise_rjct_sda;
    volatile INTN         xfer_progress;
};

struct device {
    struct device *parent;
    const char    *init_name; /* initial name of the device */
    void (*release)(struct device *dev);
};

/**
 * enum irqreturn
 * @IRQ_NONE        interrupt was not from this device
 * @IRQ_HANDLED     interrupt was handled by this device
 * @IRQ_WAKE_THREAD handler requests to wake the handler thread
 */
enum irqreturn {
    IRQ_NONE,
    IRQ_HANDLED,
    IRQ_WAKE_THREAD,
    IRQ_FAIL,
};

typedef enum irqreturn irqreturn_t;

#define I2C_SMBUS_BLOCK_MAX 32
union i2c_smbus_data {
    unsigned char  byte;
    unsigned short word;
    unsigned char  block[I2C_SMBUS_BLOCK_MAX + 2];
};

/*
 * i2c_adapter is the structure used to identify a physical i2c bus along
 * with the access algorithms necessary to access it.
 */
struct i2c_adapter {
    struct module *owner;
    unsigned int   id;
    unsigned int class;               /* classes to allow probing for */
    const struct i2c_algorithm *algo; /* the algorithm to access the bus */
    void                       *algo_data;
    /* data fields that are valid for all devices */
    unsigned int  level;   /* nesting level for lockdep */
    int           timeout; /* in jiffies */
    int           retries;
    struct device dev; /* the adapter device */
    int           nr;
    char          name[48];
};

/*
 * The following structs are for those who like to implement new bus drivers:
 * i2c_algorithm is the interface to a class of hardware solutions which can
 * be addressed using the same bus algorithms - i.e. bit-banging or the PCF8584
 * to name two of the most common.
 */
struct i2c_algorithm {
    /* If an adapter algorithm can't do I2C-level access, set master_xfer to
    NULL. If an adapter algorithm can do SMBus access, set smbus_xfer. If
    set to NULL, the SMBus protocol is simulated using common I2C messages */
    /* master_xfer should return the number of messages successfully processed,
    or a negative value on error */
    int (*master_xfer)(struct i2c_adapter *adap, struct i2c_msg *msgs, int num);
    int (*smbus_xfer)(
        struct i2c_adapter *adap, unsigned short addr, unsigned short flags,
        char read_write, unsigned char command, int size,
        union i2c_smbus_data *data);

    /* To determine what the adapter supports */
    unsigned int (*functionality)(struct i2c_adapter *);
};

#define EIO 5
#define ENOMEM 12
#define EBUSY 16
#define ENODEV 19
#define ENOSYS 38
#define EPROTONOSUPPORT 93
#define ETIMEDOUT 110

#define USEC_PER_SEC 1000000L

#define IRQF_TRIGGER_NONE 0x00000000
#define IRQF_TRIGGER_RISING 0x00000001
#define IRQF_TRIGGER_FALLING 0x00000002
#define IRQF_TRIGGER_HIGH 0x00000004
#define IRQF_TRIGGER_LOW 0x00000008
#define IRQF_TRIGGER_MASK                                                      \
  (IRQF_TRIGGER_HIGH | IRQF_TRIGGER_LOW | IRQF_TRIGGER_RISING |                \
   IRQF_TRIGGER_FALLING)
#define IRQF_TRIGGER_PROBE 0x00000010

/* To determine what functionality is present */

#define I2C_FUNC_I2C 0x00000001
#define I2C_FUNC_10BIT_ADDR 0x00000002
#define I2C_FUNC_PROTOCOL_MANGLING 0x00000004 /* I2C_M_NOSTART etc. */
#define I2C_FUNC_SMBUS_PEC 0x00000008
#define I2C_FUNC_SMBUS_BLOCK_PROC_CALL 0x00008000 /* SMBus 2.0 */
#define I2C_FUNC_SMBUS_QUICK 0x00010000
#define I2C_FUNC_SMBUS_READ_BYTE 0x00020000
#define I2C_FUNC_SMBUS_WRITE_BYTE 0x00040000
#define I2C_FUNC_SMBUS_READ_BYTE_DATA 0x00080000
#define I2C_FUNC_SMBUS_WRITE_BYTE_DATA 0x00100000
#define I2C_FUNC_SMBUS_READ_WORD_DATA 0x00200000
#define I2C_FUNC_SMBUS_WRITE_WORD_DATA 0x00400000
#define I2C_FUNC_SMBUS_PROC_CALL 0x00800000
#define I2C_FUNC_SMBUS_READ_BLOCK_DATA 0x01000000
#define I2C_FUNC_SMBUS_WRITE_BLOCK_DATA 0x02000000
#define I2C_FUNC_SMBUS_READ_I2C_BLOCK 0x04000000  /* I2C-like block xfer */
#define I2C_FUNC_SMBUS_WRITE_I2C_BLOCK 0x08000000 /* w/ 1-byte reg. addr. */

#define I2C_FUNC_SMBUS_BYTE                                                    \
  (I2C_FUNC_SMBUS_READ_BYTE | I2C_FUNC_SMBUS_WRITE_BYTE)
#define I2C_FUNC_SMBUS_BYTE_DATA                                               \
  (I2C_FUNC_SMBUS_READ_BYTE_DATA | I2C_FUNC_SMBUS_WRITE_BYTE_DATA)
#define I2C_FUNC_SMBUS_WORD_DATA                                               \
  (I2C_FUNC_SMBUS_READ_WORD_DATA | I2C_FUNC_SMBUS_WRITE_WORD_DATA)
#define I2C_FUNC_SMBUS_BLOCK_DATA                                              \
  (I2C_FUNC_SMBUS_READ_BLOCK_DATA | I2C_FUNC_SMBUS_WRITE_BLOCK_DATA)
#define I2C_FUNC_SMBUS_I2C_BLOCK                                               \
  (I2C_FUNC_SMBUS_READ_I2C_BLOCK | I2C_FUNC_SMBUS_WRITE_I2C_BLOCK)

#define I2C_FUNC_SMBUS_EMUL                                                    \
  (I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE | I2C_FUNC_SMBUS_BYTE_DATA |     \
   I2C_FUNC_SMBUS_WORD_DATA | I2C_FUNC_SMBUS_PROC_CALL |                       \
   I2C_FUNC_SMBUS_WRITE_BLOCK_DATA | I2C_FUNC_SMBUS_I2C_BLOCK |                \
   I2C_FUNC_SMBUS_PEC)

#endif /* __I2C_QUP__ */