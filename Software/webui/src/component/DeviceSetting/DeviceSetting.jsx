import React from "react";
import "./DeviceSetting.css";

function DeviceSetting() {
  return (
    <div className="device-setting">
      <h2 className="title">Cấu hình Bluetooth</h2>

      {/* Thông tin thiết bị */}
      <div className="device-info">
        <div className="info-item">
          <label>Tên thiết bị:</label>
          <input type="text" placeholder="Nhập tên thiết bị" />
        </div>
        <div className="info-item">
          <label>Tên mạng bluetooth:</label>
          <input type="text"/>
        </div>
        <div className="info-item">
          <label>Độ trễ giữa các phím:</label>
          <input type="number"/>
        </div>
      </div>

      {/* Cấu hình nút bấm */}
      <div className="button-config">
        <h3>Cấu hình nút bấm</h3>
        {[1, 2, 3, 4].map((btn) => (
          <div key={btn} className="button-row">
            <span>Button {btn}</span>
            <select>
              <option value="action1">Hành động 1</option>
              <option value="action2">Hành động 2</option>
            </select>
            <label>Edit:</label>
            <div className="info-item">
              <input type="number" placeholder="Nhập mã button" />
            </div>
          </div>
        ))}
      </div>

      {/* Tính năng nâng cao */}
      <div className="advanced">
        <h3>Advance for Experts</h3>
        <div>
          <label>Send message:</label>
          <textarea placeholder="Nhập tin nhắn gửi..." />
        </div>
        <div>
          <label>Receive message:</label>
          <textarea placeholder="Nhận tin nhắn..." />
        </div>
      </div>

      {/* Các nút hành động */}
      <div className="actions">
        <button className="review-btn">Review bảng mã</button>
        <button className="check-btn">Check cú pháp</button>
      </div>
    </div>
  );
}

export default DeviceSetting;
